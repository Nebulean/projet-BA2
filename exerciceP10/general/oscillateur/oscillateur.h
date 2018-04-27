#ifndef OSCILLATEUR_H
#define OSCILLATEUR_H

#include "vecteur.h"
#include <iostream>
#include "dessinable.h"
#include "supportadessin.h"
#include <memory>

/*!
 * Classe de base des oscillateurs.
 */
class Oscillateur : public Dessinable{
public:
  //! Constructeur d'Oscillateur.
  Oscillateur(Vecteur const& position, Vecteur const& vitesse, Vecteur const& origine, Vecteur const& direction_principale, SupportADessin* support);

  //! Méthode d'évolution propre à chaque oscillateur.
  /*!
   * Méthode d'évolution propre à chaque oscillateur. On ne peut pas la définir
   * ici, et on force la substitution dans les sous-classes. Donc cette méthode
   * est virtuelle pure.
   */
  virtual Vecteur f(double temps) = 0;

  //! Copie polymorphique.
  virtual std::unique_ptr<Oscillateur> copie() const = 0;

  //! Accesseur retournant la position.
  Vecteur P() const {return _P;}

  //! Accesseur retournant la vitesse.
  Vecteur Q() const {return _Q;}

  //! Accesseur retournant l'origine.
  Vecteur O() const {return _O;}

  //! Accesseur retournant la direction principale de l'oscillateur.
  Vecteur a() const {return _a;}

  //! Accesseur retournant la coordonnée demandée de la position.
  double P(size_t i) const {return _P.get_coord(i);}

  //! Accesseur retournant la coordonnée demandée de la vitesse.
  double Q(size_t i) const {return _Q.get_coord(i);}

  //! Accesseur retournant la coordonnée demandée de l'origine.
  double O(size_t i) const {return _O.get_coord(i);}

  //! Accesseur retournant la coordonnée demandée de la direction principale de l'oscillateur.
  double a(size_t i) const {return _a.get_coord(i);}

  //! Manipulateurs de la position.
  void setP(Vecteur const& position); // utilisé pour l'évolution

  //! Manipulateurs de la vitesse.
  void setQ(Vecteur const& vitesse); // utilisé pour l'évolution

  //! Méthode de dessin.
  /*! Méthode de dessin. On prolonge la "pureté" de cette méthode virtuelle.
   * Elle doit être redéfinie ailleurs, dans les sous-classes, donc.
   */
  virtual void dessine() = 0;


private:
  Vecteur _P; //!< Vecteur des n paramètres du système.
  Vecteur _Q; //!< Vecteur de dérivée de _P.
  Vecteur _O; //!< Vecteur de l'origine de l'oscillateur.
  Vecteur _a; //!< Vecteur de direction principale.

  //! Utilisation du polymorphisme pour l'opérateur d'affichage.
  virtual void affiche(std::ostream& flot_de_sortie) const = 0;
};

#endif // OSCILLATEUR_H
