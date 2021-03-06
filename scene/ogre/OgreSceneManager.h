///
/// @file OgreSceneManager.h
/// @author Mancobian Poemandres
/// @license BSD License
///
/// Copyright (c) MMX by The Secret Design Collective
/// All rights reserved
///
/// Redistribution and use in source and binary forms, with or without
/// modification, are permitted provided that the following conditions are met:
///
///    * Redistributions of source code must retain the above copyright notice,
/// 		this list of conditions and the following disclaimer.
///    * Redistributions in binary form must reproduce the above copyright notice,
/// 		this list of conditions and the following disclaimer in the documentation
/// 		and/or other materials provided with the distribution.
///    * Neither the name of The Secret Design Collective nor the names of its
/// 		contributors may be used to endorse or promote products derived from
/// 		this software without specific prior written permission.
///
/// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
/// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
/// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
/// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
/// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
/// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
/// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
/// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
/// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
/// USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
///

#ifndef RSSD_OGRESCENEMANAGER_H_
#define RSSD_OGRESCENEMANAGER_H_

#include <OGRE/Ogre.h>
#include <OgreOSMScene.h>
#include "scene/SceneManager.h"

namespace RSSD {

class OgreSceneManager : public RSSD::SceneManager
{
public:
	OgreSceneManager();
	virtual ~OgreSceneManager();
	virtual bool load(const std::string &filename);
	virtual bool unload();
	virtual bool update(const float64_t elapsed);

protected:
	bool createOgre();
	void destroyOgre();
	bool createRenderer();
	void destroyRenderer();
	bool createWindow();
	void destroyWindow();
	bool createSceneLoader();
	void destroySceneLoader();

	Ogre::Root *mRoot;
	Ogre::RenderSystem *mRenderSystem;
	Ogre::RenderWindow *mRenderWindow;
	Ogre::SceneManager *mSceneManager;
	Ogre::Camera *mCamera;
	Ogre::Viewport *mViewport;
	OSMScene *mSceneLoader;
}; /// class OgreSceneManager

} /// namespace RSSD

#endif // RSSD_OGRESCENEMANAGER_H_
