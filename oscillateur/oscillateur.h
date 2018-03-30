#ifndef OSCILLATEUR_H
#define OSCILLATEUR_H

#include "../vecteur/vecteur.h"
/* Un oscillateur EST un dessinable. De plus, pour ne pas avoir à le ré-importer
 * partout cette classe.
 * Remarque: Pour ne pas tout casser, oscillateur N'EST PLUS un dessinable.
 */
// #include "../dessinable/dessinable.h"
#include <initializer_list>
#include <iostream>

class Oscillateur{
public:
  // constructeurs
  Oscillateur(std::initializer_list<double> const&, std::initializer_list<double> const&, std::initializer_list<double> const&, std::initializer_list<double> const&);
  virtual Vecteur f(double t) = 0; // marquer toute les fonctions substituées à celle-ci en utilisant override.

  // accesseurs
  Vecteur P() const {return _P;}; // pas très optimisé, non ?
  Vecteur Q() const {return _Q;}; // pas très optimisé, non ?
  Vecteur a() const {return _a;};

  // manipulateurs
  void setP(Vecteur const&); // utilisé pour l'évolution
  void setQ(Vecteur const&); // utilisé pour l'évolution

  // méthodes héritées
  // virtual void dessine() = 0;


private:
  Vecteur _P; // Vecteur des n paramètres du système.
  Vecteur _Q; // Vecteur de dérivée de _P.
  Vecteur _O; // Vecteur de l'origine de l'oscillateur
  Vecteur _a; // Vecteur de direction principale
};

// surcharge externe
std::ostream& operator<<(std::ostream&, Oscillateur const&);

#endif // OSCILLATEUR_H
