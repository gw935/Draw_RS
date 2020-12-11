#ifndef KNOTPOS_H
#define KNOTPOS_H

#include <QColor>

/**
 * @brief Klasse zum Speichern der Werte eines Knotens.
 */
class knotpos
{
public:
    knotpos(int x, int y, int size, int value);                                     //Konstruktor für Endknoten.
    knotpos(int x, int y, int size, int value, knotpos *left, knotpos *right);      //Konstruktor für Knoten mit Nachbarn.

    /**
     * ---------------------------
     * Getter und Setter Methoden!
     * ---------------------------
     */

    int getX();
    int getY();
    int getSize();
    int getValue();

    knotpos *getLeft();
    knotpos *getRight();

    void setLeft(knotpos *k);
    void setRight(knotpos *k);

    void setSquare() {square = true;}
    void setColor(QColor *c) {color = c;}

    bool getSquare() {return square;}
    QColor *getColor() {return color;}

    /**
     * ------------------------------------
     * Ende der Getter und Setter Methoden.
     * ------------------------------------
     */
private:
    int x;                                  //x-Position des Knotens
    int y;                                  //y-Position des Knotens
    int size;                               //Größe des Knotens
    int value;                              //Textwert des Knotens

    QColor *color = nullptr;                //Optionale Knotenfarbe
    bool square = false;                    //Optionale Knotenform

    knotpos *leftK;                         //Linker Knoten
    knotpos *rightK;                        //Rechter Knoten
};

#endif
