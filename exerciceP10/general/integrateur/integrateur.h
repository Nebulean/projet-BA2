#ifndef H_INTEGRATEUR
#define H_INTEGRATEUR

#include "oscillateur.h"

/*!
 * Classe de base des Intégrateurs.
 */
class Integrateur{
public:
  /* Le constructeur par défaut est suffisent, car il n'y a
   * rien à initialiser dans cette classe.
   */
   virtual ~Integrateur() {}

  //! Méthode qui fait évoluer l'oscillateur donné en argument.
  /*! Méthode qui fait évoluer l'oscillateur donné en argument.
   * Elle est virtuelle pure, car on ne peut pas la définir ici, et ça force la
   * substitution dans les autres intégrateurs.
   */
  virtual void evolue(Oscillateur& oscillateur, double pas_de_temps, double temps) = 0;
};




// //! Namespace contenant un type enum qui liste l'ensemble des intégrateurs.
// namespace integr
// {
//   //! Type qui contient la liste des tous les intégrateurs.
//   /*!
//    * Chaque element de ce type a une valeur par défaut. Cette valeur commence
//    * à 0.
//    */
//   enum EnsIntegr { EC, NM, RK4 };
// }

#endif // H_INTEGRATEUR
