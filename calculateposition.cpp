#include "calculateposition.h"

/**
 * @brief Methode zum Eintragen der Positionen.
 * @param tree
 *          Übergebener Baum
 * @param delta_x
 *          deltaX zur Verschiebung
 * @param delta_y
 *          deltaY zur Verschiebung
 * @param size
 *          Knotengröße
 * @param renderArea
 *          Zeichenobjekt
 * @return Startknoten
 */
knotpos* calculateposition::positionen_eintragen(struct TreeNode* tree,int delta_x, int delta_y, RenderArea* renderArea){
    if(tree == nullptr)
    {
        throw invalid_argument("Die uebergebene TreeNode ist ein Nullpointer.");
    }
    if(renderArea == nullptr)
    {
        throw invalid_argument("Die uebergebene RenderArea ist ein Nullpointer.");
    }
    if(delta_x < 1)
    {
        throw invalid_argument("Die uebergebene delta_x ist zu klein.");
    }
    if(delta_y < 50)
    {
        throw invalid_argument("Die uebergebene delta_y ist zu klein.");
    }

    int konstanten[3] {0};
    konstanten[0] = delta_x;
    konstanten[1] = delta_y;
    if(delta_x >= delta_y){konstanten[2] = delta_x /2 -10;}
    else{konstanten[2] = delta_y /2 -10;}
    knotpos* start =nullptr;
    start = positionen_berechnen(tree, konstanten, 0, 1, renderArea);
    renderArea->addKnot(start);
    return start;
}

/**
 * @brief calculateposition::positionen_berechnen
 * @param tree
 *          Übergebener Baum
 * @param konstanten
 *          optische konstante Werte zusammengefasst im array
 * @param atm
 *          die übergabe der actuellen positionen
 * @param tiefe
 *          die Stufe des Knotens
 * @param renderArea
 *          Zeichenobjekt
 * @return  position actueller Knoten
 *
 */
knotpos* calculateposition::positionen_berechnen(struct TreeNode* tree, int *konstanten, int atm, int tiefe, RenderArea* renderArea){

    knotpos *PosRight = nullptr, *PosLeft = nullptr;
    //if(tree->key != 0){
    //an die linkeste Position
    //falls es kein links mehr gibt bleibt Pos links nullptr
    TreeNode* halter = tree->left;
    if(halter != nullptr){
        PosLeft = positionen_berechnen(halter, konstanten, atm,  tiefe +1, renderArea);
    }

    //Mitte befindet sich rechts neben allen linken unterknoten.
    if(PosLeft != nullptr) {atm = letzte_breite(PosLeft);}

    //die neuen Position ist Delta x entfernt von nächsten Punkt entfernt
    atm += konstanten[0];


    //wird mit der rechten Seite fortgeführt
    halter = tree->right;
    if(halter != nullptr){
       PosRight = positionen_berechnen(halter, konstanten, atm, tiefe +1, renderArea);
    }
    int dicke = dynamische_groesse(tiefe, konstanten[2]);
    knotpos *me = new knotpos(atm, tiefe * konstanten[1], dicke, tree->key, PosLeft, PosRight);


    //farbe für RS knoten
    if(tree->color == "RED"){me->setColor(new QColor(Qt::red));}

    renderArea->addKnot(me);

    return me;                  //ich gebe meinem Vater meine position
    //}
    //return nullptr;
}


/**
 * @brief suche der letzten position links von der aktuellen
 * @param lead
 *          übergebener Knoten
 * @return
 */
int calculateposition::letzte_breite(knotpos* lead){
    int zaehler = lead->getX();
    if(lead->getRight() != nullptr){
        zaehler = letzte_breite(lead->getRight());
    }
    else return zaehler;

    return zaehler;
}



/**
 * @brief änderung der Knotengröße abhängig von der Tiefe
 * @param tiefe
 *          die Stufe des Knotens
 * @param size
 *          Optische größe des Knotens
 * @return
 */
int calculateposition::dynamische_groesse(int tiefe, int size){

    //knoten darf nicht kleiner werden als 25
    if(size - (size/10 * tiefe) >= 25){
        return size - (size/10 * tiefe);
    }
    else
        return 25;
}

