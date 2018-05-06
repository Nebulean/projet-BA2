#include <QKeyEvent>
#include <QTimerEvent>
#include <QMatrix4x4>
#include <cmath>
#include "glwidget.h"
#include "integrateur.h"
#include "eulercromer.h"
#include "rungekutta.h"
#include "newmark.h"
using namespace std;
// using namespace integr;

void GLWidget::initSys(){

  /* Pendule: masse, longueur, viscosité, supportadessin, P, Q, O, a.
   * Ressort: masse, elasticité, viscosité, supportadessin, P, Q, O, a.
   * Torsion: moment d'inertie, cte de torsion, friction, support, P, Q, O, a.
   */
  Pendule p(2, 2, 0.5, &vue, {M_PI/3}, {0.0}, {0.0, 0.0, 0.0}, {1.0, 0.0, 0.0});
  _sys+=p;

  Ressort r(0.25, 0.33, 0.15, &vue, {0.18}, {0.0}, {-2.0, 0.0, 0.0}, {0.8, 0.0, 0.6});
  _sys+=r;

  // double moment_inertie, double constante_torsion, double friction, SupportADessin* support, Vecteur P = {M_PI/4}, Vecteur Q = {0.0}, Vecteur O = {0.0}, Vecteur a = {1.0, 0.0}
  Torsion t(1, 1, 0, &vue, {M_PI/4}, {0.0}, {2.0, 0.0, 0.0}, {1.0, 0.0, 0.0});
  _sys+=t;
}




// ======================================================================
void GLWidget::initializeGL()
{
  vue.init();
  timerId = startTimer(20);

  // on initialise le Systeme.
  initSys();
}

// ======================================================================
void GLWidget::resizeGL(int width, int height)
{
  /* On commence par dire sur quelle partie de la
   * fenêtre OpenGL doit dessiner.
   * Ici on lui demande de dessiner sur toute la fenêtre.
   */
  glViewport(0, 0, width, height);

  /* Puis on modifie la matrice de projection du shader.
   * Pour ce faire on crée une matrice identité (constructeur
   * par défaut), on la multiplie par la droite par une matrice
   * de perspective.
   * Plus de détail sur cette matrice
   *     http://www.songho.ca/opengl/gl_projectionmatrix.html
   * Puis on upload la matrice sur le shader à l'aide de la
   * méthode de la classe VueOpenGL
   */
  QMatrix4x4 matrice;
  matrice.perspective(70.0, qreal(width) / qreal(height ? height : 1.0), 1e-3, 1e5);
  vue.setProjection(matrice);
}

// ======================================================================
void GLWidget::paintGL()
{
  /* Cette méthode redessine la scène.
   * Elle est appellée lorsqu'on utilise updateGL().
   */
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  // c.dessine();

  // vue.dessineAxesCamera();
  _sys.dessine();
}


// ======================================================================
void GLWidget::keyPressEvent(QKeyEvent* event)
{
  constexpr double petit_angle(5.0); // en degrés
  constexpr double petit_pas(1.0);

  switch (event->key()) {

  case Qt::Key_Left:
    vue.rotate(petit_angle, 0.0, -1.0, 0.0);
    //vue.rotate(petit_angle, 0.0, 0.0, -1.0);
    break;

  case Qt::Key_Right:
    vue.rotate(petit_angle, 0.0, +1.0, 0.0);
    //vue.rotate(petit_angle, 0.0, 0.0, +1.0);
    break;

  case Qt::Key_Up:
    vue.rotate(petit_angle, -1.0, 0.0, 0.0);
    break;

  case Qt::Key_Down:
    vue.rotate(petit_angle, +1.0, 0.0, 0.0);
    break;

  case Qt::Key_PageUp:
  case Qt::Key_W:
    vue.translate(0.0, 0.0,  petit_pas);
    break;

  case Qt::Key_PageDown:
  case Qt::Key_S:
    vue.translate(0.0, 0.0, -petit_pas);
    break;

  case Qt::Key_A:
    vue.translate( petit_pas, 0.0, 0.0);
    break;

  case Qt::Key_D:
    vue.translate(-petit_pas, 0.0, 0.0);
    break;

  case Qt::Key_R:
    vue.translate(0.0, -petit_pas, 0.0);
    break;

  case Qt::Key_F:
    vue.translate(0.0,  petit_pas, 0.0);
    break;

  case Qt::Key_Q:
    vue.rotate(petit_angle, 0.0, 0.0, -1.0);
    //vue.rotate(petit_angle, 0.0, -1.0, 0.0);
    break;

  case Qt::Key_E:
    vue.rotate(petit_angle, 0.0, 0.0, +1.0);
    //vue.rotate(petit_angle, 0.0, +1.0, 0.0);
    break;

  case Qt::Key_Home:
    vue.initializePosition();
    break;

  case Qt::Key_Space:
    pause();
    break;

  // lorsqu'on appuie sur B, la visibilité de la boussole s'inverse.
  case Qt::Key_B:
    vue.toggleBoussole();
    break;

  // lorsqu'on appuie sur §, le mode debug est activé.
  case Qt::Key_section:
    vue.toggleDebugMode();
    break;

  case Qt::Key_V:
    vue.toggleVue();
    break;

  // case Qt::Key_I:
  //   // on commence par désallouer l'intégrateur actuel
  //   Integrateur* tmp(_integrateur);
  //   _integrateur = nullptr;
  //   // delete tmp;
  //
  //   // ensuite, on choisi l'intégrateur suivant
  //   // change_integrateur(_integrateur);
  //   break;

  };

  updateGL(); // redessine
}

// ======================================================================
void GLWidget::timerEvent(QTimerEvent* event)
{
  Q_UNUSED(event);

  double dt = chronometre.restart() / 1000.0;

  /* En gros, on aligne le pas de temps du Systeme avec le pas de temps de Qt,
   * puis on fait évoluer le système avec son propre dt.
   */
  _sys.setdt(dt);

  // c.evolue(dt);
  _sys.evolue();
  updateGL();
}

// ======================================================================
void GLWidget::pause()
{
  if (timerId == 0) {
    // dans ce cas le timer ne tourne pas alors on le lance
    timerId = startTimer(20);
    chronometre.restart();
  } else {
    // le timer tourne alors on l'arrête
    killTimer(timerId);
    timerId = 0;
  }
}



/*!
 * Enregistre la dernière position
 */
void GLWidget::mousePressEvent(QMouseEvent* event)
{
  lastMousePosition = event->pos();
}


/*!
 * Mouvement de la souris. click & drag.
 */
void GLWidget::mouseMoveEvent(QMouseEvent* event)
{
  /* If mouse tracking is disabled (the default), the widget only receives
   * mouse move events when at least one mouse button is pressed while the
   * mouse is being moved.
   *
   * Pour activer le "mouse tracking" if faut lancer setMouseTracking(true)
   * par exemple dans le constructeur de cette classe.
   */

  if (event->buttons() & Qt::LeftButton) {
	constexpr double petit_angle(.4); // en degrés

	// Récupère le mouvement relatif par rapport à la dernière position de la souris
	QPointF d = event->pos() - lastMousePosition;
	lastMousePosition = event->pos();

	vue.rotate(petit_angle * d.manhattanLength(), d.y(), d.x(), 0);

	update();
  }
}

// pour changer d'intégrateur...
// void GLWidget::change_integrateur(Eulercromer* IEC){
//   Q_UNUSED(IEC);
//   _integrateur = new Newmark; // par défaut, on l'initialise à une précision 1e-6.
// }
//
// void GLWidget::change_integrateur(Newmark* INM){
//   Q_UNUSED(INM);
//   _integrateur = new RungeKutta;
// }
//
// void GLWidget::change_integrateur(RungeKutta* IRK){
//   Q_UNUSED(IRK);
//   _integrateur = new Eulercromer;
// }

//! Choisi un nouvel intégrateur en fonction du précédent.
// void GLWidget::choose_integrateur(){
//   switch (_integrateurActuel) {
//     case EC:
//       // _integrateur = new Newmark; // par défaut, on l'initialise à une précision 1e-6.
//       // _integrateurActuel = NM;
//       break;
//
//     case NM:
//       // _integrateur = new RungeKutta;
//       // _integrateurActuel = RK4;
//       break;
//
//     case RK4:
//       // _integrateur = new Eulercromer;
//       // _integrateurActuel = EC;
//       break;
//   }
// }
