#include "Appli.hpp"

#include <limits>

static const int node_radius_default = 2;
static float node_radius = node_radius_default;
static int alpha_edge = 20;

Appli::Appli(uint largeur, uint hauteur) :
    m_fenetre(sf::VideoMode(largeur, hauteur), "C++ graph visualize"),
    m_largeur(largeur),
    m_hauteur(hauteur),
    m_interpoler_couleurs(false),
    m_g(nullptr),
    m_vue(sf::FloatRect(0, 0, largeur, hauteur)),
    m_montre_etiquette(false),
    needsRefresh(true),
    m_update_lock(PTHREAD_MUTEX_INITIALIZER),
    m_is_panning(false)
{
    m_fenetre.setFramerateLimit(60);

    m_vue.setCenter(largeur / 2.f, hauteur / 2.f);
    m_fenetre.setView(m_vue);
}

void Appli::setGraphe(ValuedGraph &g) {
    m_g = &g;

    if (m_edges.empty() || m_nodes.empty()) {
        calculerFormesGeometriques();
    }
}

bool Appli::running() const {
    return m_fenetre.isOpen();
}

void Appli::exec() {
    if (running()) {
        traiter_evenements();
        if (needsRefresh) {dessiner(); needsRefresh = false;}
    }
}

void Appli::handleEdgeAlphaChange(sf::Event e) {
    bool changed = false;
    if (e.key.code == sf::Keyboard::Down && alpha_edge - 1 >= 10) {
        alpha_edge--;
        changed = true;
    } else if (e.key.code == sf::Keyboard::Up && alpha_edge + 1 < 255) {
        alpha_edge++;
        changed = true;
    }

    if (changed) {
        std::cout << (e.key.code == sf::Keyboard::Up ? "[+]" : "[-]")
                  << " New alpha for edges: " << alpha_edge << std::endl;

        // Mise à jour des couleurs des arêtes
        for (auto &edge_pair : m_edges) {
            sf::Color color(0, 0, 0, alpha_edge);
            edge_pair.second.first.color = color;
            edge_pair.second.second.color = color;
        }

        needsRefresh = true;
    }
}

void Appli::handleNodeSizeChange(sf::Event e) {
    bool changed = false;
    if (e.key.code == sf::Keyboard::Left && node_radius - 0.5f >= 2.0f) {
        node_radius -= 0.5f;
        changed = true;
    } else if (e.key.code == sf::Keyboard::Right && node_radius + 0.5f <= 30.0f) {
        node_radius += 0.5f;
        changed = true;
    }

    if (changed) {
        std::cout << (e.key.code == sf::Keyboard::Right ? "[+]" : "[-]")
                  << " New node radius: " << node_radius << std::endl;

        for (auto &node_pair : m_nodes) {
            float oldRadius = node_pair.second.getRadius();
            node_pair.second.setRadius(node_radius);

            sf::Vector2f pos = node_pair.second.getPosition();
            pos.x = pos.x + oldRadius - node_radius;
            pos.y = pos.y + oldRadius - node_radius;
            node_pair.second.setPosition(pos);
        }

        needsRefresh = true;
    }
}


void Appli::traiter_evenements() {
    sf::Event e;
    while (m_fenetre.pollEvent(e)) {
        switch (e.type) {
            case sf::Event::Closed:
                m_fenetre.close();
            break;
            case sf::Event::KeyPressed:
                    if (e.key.code == sf::Keyboard::K) {
                        std::cout << "Closing key pressed! Exiting." << std::endl;
                        m_fenetre.close();
                    }
                    else if (e.key.code == sf::Keyboard::I) {
                        m_interpoler_couleurs = !m_interpoler_couleurs;
                        std::cout << "Interpolation " << (m_interpoler_couleurs ? "enabled" : "disabled") << std::endl;
                     } else if (e.key.code == sf::Keyboard::Down || e.key.code == sf::Keyboard::Up) {
                         handleEdgeAlphaChange(e);
                         //changing nodes size
                     } else if (e.key.code == sf::Keyboard::Left || e.key.code == sf::Keyboard::Right) {
                         handleNodeSizeChange(e);
                    } else if (e.key.code == sf::Keyboard::R) {
                        resetView();
                        std::cout << "Reset view" << std::endl;
                    }
            break;
            case sf::Event::MouseWheelScrolled:
                if (e.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
                    sf::Vector2i pixelPos = sf::Mouse::getPosition(m_fenetre);

                    sf::Vector2f worldPos = m_fenetre.mapPixelToCoords(pixelPos, m_vue);

                    float zoomFactor = (e.mouseWheelScroll.delta > 0) ? 0.9f : 1.1f;

                    m_vue.zoom(zoomFactor);

                    sf::Vector2f newCenter = worldPos + (m_vue.getCenter() - worldPos) * zoomFactor;
                    m_vue.setCenter(newCenter);

                    m_fenetre.setView(m_vue);

                    needsRefresh = true;
                }
            break;

            case sf::Event::MouseButtonPressed:
                if (e.mouseButton.button == sf::Mouse::Left) {
                    m_is_panning = true;
                    m_last_mouse_pos = sf::Vector2f(e.mouseButton.x, e.mouseButton.y);
                }
            break;

            case sf::Event::MouseButtonReleased:
                if (e.mouseButton.button == sf::Mouse::Left) {
                    m_is_panning = false;
                }
            break;

            case sf::Event::MouseMoved:
                if (m_is_panning) {
                    sf::Vector2f current_mouse_pos(e.mouseMove.x, e.mouseMove.y);
                    sf::Vector2f delta = m_last_mouse_pos - current_mouse_pos;

                    delta.x *= m_vue.getSize().x / m_fenetre.getSize().x;
                    delta.y *= m_vue.getSize().y / m_fenetre.getSize().y;

                    m_vue.move(delta);
                    m_fenetre.setView(m_vue);
                    m_last_mouse_pos = current_mouse_pos;

                    needsRefresh = true;
                }
            break;
            default:
                break;
        }
    }
}

void Appli::resetView() {
    m_vue = sf::View(sf::FloatRect(0.f, 0.f, m_largeur, m_hauteur));
    m_vue.setCenter(m_largeur / 2.f, m_hauteur / 2.f);
    m_fenetre.setView(m_vue);
    needsRefresh = true;
}

void Appli::toggleInterpolation() {
    m_interpoler_couleurs = !m_interpoler_couleurs;
    std::cout << "Interpolation " << (m_interpoler_couleurs ? "enabled" : "disabled") << std::endl;
    needsRefresh = true;
}


void Appli::dessiner() {
    m_fenetre.clear(sf::Color::Black);
    m_fenetre.setView(m_vue);

    pthread_mutex_lock(&m_update_lock);

    for (const auto &e: m_edges) {
        const Edge &edge = e.first;

        sf::Vertex line[2] = {
            sf::Vertex(e.second.first.position),
            sf::Vertex(e.second.second.position)
        };

        if (m_interpoler_couleurs) {
            Node start = edge.getStart();
            Node end = edge.getEnd();

            Color colorStart = m_g->getColorsProperties().value(start);
            Color colorEnd = m_g->getColorsProperties().value(end);

            line[0].color = sf::Color(colorStart.getR(), colorStart.getG(),
                                      colorStart.getB(), colorStart.getAlpha());
            line[1].color = sf::Color(colorEnd.getR(), colorEnd.getG(),
                                      colorEnd.getB(), colorEnd.getAlpha());
        } else {
            sf::Color sfmlColor(10, 10, 230, alpha_edge);
            line[0].color = sfmlColor;
            line[1].color = sfmlColor;
        }

        m_fenetre.draw(line, 2, sf::Lines);
    }

    for (const auto &n: m_nodes) {
        m_fenetre.draw(n.second);
    }

    pthread_mutex_unlock(&m_update_lock);
    m_fenetre.display();
}

void Appli::creerFormeSommet(const Node &n) {
    sf::CircleShape shape(node_radius_default);

    //lock mutex for read
    pthread_mutex_lock(&m_update_lock);
    Color c = m_g->getColorsProperties().value(n);
    pthread_mutex_unlock(&m_update_lock);

    sf::Color color(c.getR(), c.getG(), c.getB(), c.getAlpha());
    shape.setFillColor(color);
    m_nodes.emplace(n, shape);
}

void Appli::creerFormeArete(Edge e) {
    //lock for read
    pthread_mutex_lock(&m_update_lock);
    sf::Vector2f startPos(m_g->getPositionsProperties().value(e.getStart()).getX(),
                        m_g->getPositionsProperties().value(e.getStart()).getY());
    sf::Vector2f endPos(m_g->getPositionsProperties().value(e.getEnd()).getX(),
                      m_g->getPositionsProperties().value(e.getEnd()).getY());
    pthread_mutex_unlock(&m_update_lock);

    sf::Vertex start;
    sf::Vertex end;
    start.position = startPos;
    end.position = endPos;

    m_edges.emplace(e, std::pair(start, end));
}

void Appli::calculerFormesGeometriques() {
    m_nodes.clear();
    m_edges.clear();

    for (auto &n: m_g->getNodes()) {
        creerFormeSommet(n);
    }

    for (auto &e: m_g->getEdges()) {
        creerFormeArete(e);
    }
}

void Appli::treatAdd(const Node &n) {
    needsRefresh = true;
}

void Appli::treatAdd(const Edge &e) {
    needsRefresh = true;
}

void Appli::treatDelete(const Edge &e) {
    needsRefresh = true;
    //lock for edit
    pthread_mutex_lock(&m_update_lock);
    m_g->deleteEdge(e);
    pthread_mutex_unlock(&m_update_lock);
}

void Appli::treatDelete(const Node &n) {
    pthread_mutex_lock(&m_update_lock);
    dessiner();
    m_g->deleteNode(n);
    pthread_mutex_unlock(&m_update_lock);
}

void Appli::treatPropertyChange(const Node &n) {
    needsRefresh = true;

    pthread_mutex_lock(&m_update_lock);
    Coord pos = m_g->getPositionsProperties().value(n);
    pthread_mutex_unlock(&m_update_lock);
    m_nodes[n].setPosition(sf::Vector2f(pos.getX(), pos.getY()));

    for (auto &edge_pair : m_edges) {
        const Edge &edge = edge_pair.first;

        if (edge.getStart() == n || edge.getEnd() == n) {
            pthread_mutex_lock(&m_update_lock);
            sf::Vector2f startPos(m_g->getPositionsProperties().value(edge.getStart()).getX(),
                                 m_g->getPositionsProperties().value(edge.getStart()).getY());
            sf::Vector2f endPos(m_g->getPositionsProperties().value(edge.getEnd()).getX(),
                               m_g->getPositionsProperties().value(edge.getEnd()).getY());
            pthread_mutex_unlock(&m_update_lock);

            edge_pair.second.first.position = startPos;
            edge_pair.second.second.position = endPos;
        }
    }
}

void Appli::treatPropertyChange(const Edge &e) {
    needsRefresh = true;
}



