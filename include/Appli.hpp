#ifndef APPLI_HPP
#define APPLI_HPP
#include <SFML/Graphics.hpp>
#include "ValuedGraph.hpp"
#include "GraphObserver.hpp"

class Appli: public GraphObserver
{
public:
    Appli(unsigned int largeur, unsigned int hauteur);

    void setGraphe(ValuedGraph &g);

    bool running() const;
    void exec();

    void treatAdd(const Node &n) override ;
    void treatAdd(const Edge &e) override ;

    void treatDelete(const Edge &e) override ;
    void treatDelete(const Node &n) override ;

    void treatPropertyChange(const Node &n) override ;
    void treatPropertyChange(const Edge &e) override ;

private:
    sf::View m_vue;
    sf::RenderWindow m_fenetre;
    sf::Font m_font;

    std::map<Node, sf::CircleShape> m_nodes;
    std::map<std::string, sf::CircleShape> m_etiquette;
    std::map<Edge, std::pair<sf::Vertex, sf::Vertex> > m_edges;

    ValuedGraph *m_g;

    bool m_montre_etiquette;
    bool m_interpoler_couleurs;
    bool needsRefresh;
    bool m_is_panning;
    sf::Vector2f m_last_mouse_pos;

    static const float RAYON;
    static const std::string FICHIER_FONT;
    pthread_mutex_t m_update_lock;

    unsigned int m_largeur, m_hauteur;

    void toggleNeedsRefresh();
    void updateNodePosition(const Node &n);
    void toggleInterpolation();

    void resetView();

    void traiter_evenements();
    void dessiner();

    void creerFormeSommet(const Node &n);
    void creerFormeArete(Edge e);
    void calculerFormesGeometriques();

    void handleEdgeAlphaChange(sf::Event e);
    void handleNodeSizeChange(sf::Event e);
};

#endif // APPLI_HPP
