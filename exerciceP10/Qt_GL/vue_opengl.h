#ifndef VUEOPENGL_H
#define VUEOPENGL_H

#include <QGLShaderProgram> // Classe qui regroupe les fonctions OpenGL liées aux shaders
#include <QMatrix4x4>
#include <cmath>
#include "supportadessin.h"
#include "pendule.h"
#include "ressort.h"
#include "systeme.h"
#include "torsion.h"
#include "glsphere.h"

class VueOpenGL : public SupportADessin {
 public:
  // méthode(s) de dessin (héritée(s) de SupportADessin)
  // virtual void dessine(Contenu const& a_dessiner) override;
  virtual void dessine(Pendule const& pendule_a_dessiner) override;
  virtual void dessine(Ressort const& ressort_a_dessiner) override;
  virtual void dessine(Systeme const& systeme_a_dessiner) override;
  virtual void dessine(Torsion const& torsion_a_dessiner) override;

  //! méthode de (ré-)initialisation
  void init();
  //! méthode de (ré-)initialisation
  void initializePosition();

  // méthode set
  void setProjection(QMatrix4x4 const& projection)
  { prog.setUniformValue("projection", projection); }

  // Méthodes set
  void translate(double x, double y, double z);
  void rotate(double angle, double dir_x, double dir_y, double dir_z);

  // méthode utilitaire offerte pour simplifier
  void dessineCube(QMatrix4x4 const& point_de_vue = QMatrix4x4() );
  void dessineSphere(QMatrix4x4 const& point_de_vue = QMatrix4x4(), double rouge = 1.0, double vert = 1.0, double bleu = 1.0);
  void dessineAxes(QMatrix4x4 const& point_de_vue = QMatrix4x4(), bool translatable = true, bool en_couleur = true);
  void dessineLigne(QMatrix4x4 const& point_de_vue = QMatrix4x4(), bool en_couleur = false, double longueur = 1, double x = 1.0, double y = 0.0, double z = 0.0 );
  void dessineOscill(Oscillateur const& a_dessiner, QMatrix4x4 point_de_vue, double longueur, double coeff_diametre);

  //! Méthode de dessin des axes suivant le point de vue.
  void dessineAxesCamera();

  //! Switch changeant la visibilité de la boussole.
  void toggleBoussole() {boussoleVisible = !boussoleVisible; }

  //! Switch changeant l'état du mode debug.
  void toggleDebugMode() {debugMode = !debugMode; }

  //! Switch pour passer de la vue première personne à la vue troisième personne.
  void toggleVue() {TPS = !TPS; }

 private:
  // Un shader OpenGL encapsulé dans une classe Qt
  QGLShaderProgram prog;
  GLSphere sphere;

  //! Caméra
  QMatrix4x4 matrice_vue;
  //! Matrice qui mémorise les translations de matrice_vue
  // QMatrix4x4 translation;
  //! Matrice qui mémorise les rotations en première personne
  // QMatrix4x4 rotfps;
  //! Matrice qui mémorise les rotations en première personne et les translations de matrice_vue
  QMatrix4x4 memoire;

  //! Matrice affectée par les rotations mais pas les translations
  QMatrix4x4 boussole;
  //! Matrice qui mémorise la position des axes de la boussole
  QMatrix4x4 position;

  //! Variable d'état de la boussole, true = visible.
  bool boussoleVisible;

  //! Variable d'état du mode debug. (text activé)
  bool debugMode;

  //! Variable d'était de la vue première/troisième personne, TPS = troisième personne activée.
  bool TPS;
};

//! Convertisseur Radian -> Degrés.
double toDegree(double radian);

#endif
