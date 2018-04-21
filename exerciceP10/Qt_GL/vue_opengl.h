#ifndef VUEOPENGL_H
#define VUEOPENGL_H

#include <QGLShaderProgram> // Classe qui regroupe les fonctions OpenGL liées aux shaders
#include <QMatrix4x4>
#include "supportadessin.h"
#include "pendule.h"
#include "ressort.h"
#include "systeme.h"
#include "torsion.h"

class VueOpenGL : public SupportADessin {
 public:
  // méthode(s) de dessin (héritée(s) de SupportADessin)
  // virtual void dessine(Contenu const& a_dessiner) override;
  virtual void dessine(Pendule const& pendule_a_dessiner) override;
  virtual void dessine(Ressort const& ressort_a_dessiner) override;
  virtual void dessine(Systeme const& systeme_a_dessiner) override;
  virtual void dessine(Torsion const& torsion_a_dessiner) override;

  // méthodes de (ré-)initialisation
  void init();
  void initializePosition();

  // méthode set
  void setProjection(QMatrix4x4 const& projection)
  { prog.setUniformValue("projection", projection); }

  // Méthodes set
  void translate(double x, double y, double z);
  void rotate(double angle, double dir_x, double dir_y, double dir_z);

  // méthode utilitaire offerte pour simplifier
  void dessineCube(QMatrix4x4 const& point_de_vue = QMatrix4x4() );

 private:
  // Un shader OpenGL encapsulé dans une classe Qt
  QGLShaderProgram prog;

  // Caméra
  QMatrix4x4 matrice_vue;
};

#endif
