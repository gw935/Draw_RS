#include "showknot.h"
#include "tree.h"
#include <cstdlib>
#include <iostream>

#include <QApplication>

/**
 * @brief Startfunktion zum Erstellen eines zufällligen Baums und Anzeigen über ShowKnot::Display.
 *      Programmparameter sind optional, können aber bei Bedarf für einen modifizierten Zufallsbaum verwendet werden.
 *      Parameter:
 *      1. Maximale Anzahl an Knoten
 *      2. Mindestwert der Knoten
 *      3. Maximalwert der Knoten
 *      Die Startfunktion ist nur ein Beispiel und sollte natürlich durch den eigenen Code ausgewechselt werden.
 * @param argc - Anzahl der Parameter
 * @param argv - Liste der Parameter
 * @return Programmablauf
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    struct TreeNode* tree = NULL;
    srand (time(NULL));

    int x = 10;         //anzahl
    int rMi = 0;        //rand min
    int rMa = 100;      //rand max

    if(argc > 0){
        x = atoi(argv[1]); if (x == 0) x = 10;
        if(argc > 1){
            rMi = atoi(argv[2]); if(rMi == 0) rMi = 0;
            if(argc > 2){
                rMa = atoi(argv[3]); if(rMa == 0) rMa = 100; rMa -= rMi;
            }
        }
    }


    cout << rMi << " - " << rMa << " | " << x;
    if(rMa < rMi || rMa <= 0 || rMi < 0 || x <= 0){
        return -1;
    }

    for (int i = 0; i < x; i++) {
        int random = (rand() % (rMa + 1)) + rMi;
        tree = tree::TreeInsert(tree, random, "Info zu Schluessel " + std::to_string(random));
    }

    ShowKnot::display(tree);
    return a.exec();
}
