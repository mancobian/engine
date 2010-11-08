#include "main/Engine.h"
#include "Scene"
#include "Physics"

using namespace std;
using namespace RSSD;

Engine::Engine() :
  mRunning(false),
  mSceneManager(NULL)
{
  this->createManagers();
}

Engine::~Engine()
{
  this->destroyManagers();
}

void Engine::start()
{
  boost::mutex::scoped_lock lock(this->mMainMutex);
  if (this->mRunning) { return; }

  this->mRunning = true;
  this->mMainThread = ThreadPointer(new Thread(&Engine::run, this));
}

void Engine::stop()
{
  assert (this->mMainThread);
  this->mRunning = false;
  this->mMainThread->join();
}

void Engine::run()
{
  float64_t elapsed = 0.0f;

  while (this->mRunning)
  {
    if (!this->updateManagers(elapsed)) { break; }
  }
}

void Engine::createManagers()
{
  this->mSceneManager = new OgreSceneManager();
}

void Engine::destroyManagers()
{
  if (this->mSceneManager)
  {
    delete this->mSceneManager;
    this->mSceneManager = NULL;
  }
}

bool Engine::updateManagers(const float64_t elapsed)
{
  return this->mSceneManager->update(elapsed);
}

bool Engine::loadScene(const std::string &filename)
{
  return this->mSceneManager->load(filename);
}

bool Engine::unloadScene()
{
  return this->mSceneManager->unload();
}
