#include <chrono>

#include "ForceModel.hpp"
#include <iostream>
#include "ValuedGraph.hpp"
#include "Appli.hpp"
#include <pthread.h>
#include <thread>
using namespace std;

const int LARGEUR = 1200;
const int HAUTEUR = 800;

void * updateGraphData(void * param) {
    auto* g = (ValuedGraph *) param;
    Appli app {LARGEUR, HAUTEUR};
    app.setGraphe(*g);

    g->attach(&app);

    while(app.running())
        app.exec();

    pthread_exit(nullptr);
}

int main(int argc, char *argv[])
{
    if (argc != 2){
        cout << "Usage: ./app <graph_file>.<txt,csv>" << endl;
        return 1;
    }
    srand(time(NULL));

    string fichier (argv[1]);
    ValuedGraph g;
    if(!g.charger(fichier)){
        cout << "Erreur de chargement de fichier" << endl;
        return 1;
    }

    pthread_t th_display;
    pthread_t th_force;

    pthread_create(&th_display,nullptr, updateGraphData, &g);

    std::this_thread::sleep_for(std::chrono::milliseconds(500));

    pthread_create(&th_force,nullptr, ForceModel::dessiner, &g);

    pthread_join(th_display, nullptr);
    pthread_join(th_force, nullptr);

    return 0;
}

