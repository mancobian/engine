#include "OgreSceneManager.h"

using namespace rssd;

OgreSceneManager::OgreSceneManager() :
  mRoot(NULL),
  mRenderSystem(NULL),
  mRenderWindow(NULL),
  mSceneManager(NULL),
  mCamera(NULL),
  mViewport(NULL)
{
  this->createOgre();
}

OgreSceneManager::~OgreSceneManager()
{
  this->destroyOgre();
}

bool OgreSceneManager::createOgre()
{
  this->mRoot = new Ogre::Root("plugins.cfg", "display.cfg", "log.txt");
  this->createRenderer();
  this->createWindow();
  return true;
}

void OgreSceneManager::destroyOgre()
{
  this->destroyWindow();
  this->destroyRenderer();
  this->mRoot->shutdown();
  delete this->mRoot;
}

bool OgreSceneManager::createRenderer()
{
  /// Local vars
  bool found = false;
  Ogre::String name;
  Ogre::RenderSystem *renderer = NULL;

  /// Find a target render system
  Ogre::RenderSystemList *renderers = this->mRoot->getAvailableRenderers();
  for (uint32_t i = 0; i < renderers->size(); ++i)
  {
    renderer = renderers->at(i);
    Ogre::String name = renderer->getName();
    if (name.compare("OpenGL Rendering Subsystem") == 0)
    {
      found = true;
      break;
    }
  }
  if (!found) { this->mRenderSystem = NULL; return false; }

  /// Assign the target render system
  this->mRenderSystem = renderer;
  this->mRoot->setRenderSystem(renderer);

  /// Configure the render system
  renderer->setConfigOption("Full Screen", "No");
  renderer->setConfigOption("Video Mode", "800 x 600 @ 16-bit colour");
  return true;
}

void OgreSceneManager::destroyRenderer()
{

}

bool OgreSceneManager::createWindow()
{
  /// Create default render window
  this->mRenderWindow = this->mRoot->initialise(true, "RSSD");

  /// Create default scene manager
  this->mSceneManager = this->mRoot->createSceneManager(Ogre::ST_GENERIC);

  /// Create default camera
  this->mCamera = this->mSceneManager->createCamera("DefaultCamera");
  this->mCamera->setPosition(Ogre::Vector3(0,0,500)); ///< Position it at 500 in Z direction
  this->mCamera->lookAt(Ogre::Vector3(0,0,-300)); ///< Look back along -Z
  this->mCamera->setNearClipDistance(5);

  /// Create one viewport, entire window
  Ogre::Viewport* viewport = this->mRenderWindow->addViewport(this->mCamera);
  viewport->setBackgroundColour(Ogre::ColourValue(0,0,0));

  /// Alter the camera aspect ratio to match the viewport
  this->mCamera->setAspectRatio(Ogre::Real(viewport->getActualWidth()) / Ogre::Real(viewport->getActualHeight()));
  return true;
}

void OgreSceneManager::destroyWindow()
{
  if (this->mViewport)
  {
    assert (this->mRenderWindow != NULL);
    this->mRenderWindow->removeViewport(this->mViewport->getZOrder());
  }

  if (this->mCamera)
  {
    assert (this->mSceneManager != NULL);
    this->mSceneManager->destroyCamera(this->mCamera);
    this->mCamera = NULL;
  }

  if (this->mSceneManager)
  {
    assert (this->mRoot != NULL);
    this->mRoot->destroySceneManager(this->mSceneManager);
    this->mSceneManager = NULL;
  }

  if (this->mRenderWindow)
  {
    this->mRenderWindow->destroy();
    this->mRenderWindow = NULL;
  }
}

bool OgreSceneManager::load(const std::string &filename)
{
  return true;
}

bool OgreSceneManager::unload()
{
  return true;
}

bool OgreSceneManager::update(const double elapsed)
{
  return true;
}
