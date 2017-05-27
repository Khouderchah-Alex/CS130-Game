#pragma once

#include "Base.h"
#include "IComponent.h"
#include "btBulletDynamicsCommon.h"

class MovableComponent;
class DrawComponent;
class TransformComponent;

struct bulletObject
{
	bool hit; //true if object is hit, false otherwise
	btRigidBody *body;
	btVector3 rotationFlags;
	btVector3 movementFlags;
	btVector3 gravity;
	bulletObject(btRigidBody *b, btVector3 &rot, btVector3 &mov): 
		body(b), hit(false), rotationFlags(rot), movementFlags(mov), gravity(btVector3(0.0,-10.0, 0.0)) {}
};


/**
* @brief Component that stores Bullet Physics bodies required for PhysicsComponent
*
* When creating this entity, we are only required to call one of the appropriate functions for the desired shape
* 
*  ---Here I will provide the interfaces for each shape functions and a brief description---
*
*
* addPlane
* Explanation: Adds an infinite static plane at the indicated location
* Interface: NONE
*
* addBox: 
* Explanation: Adds a box.
* Interface: float mass(No default value), btVector3 &additionToDimensions(Default value (0,0,0))
*
* addSphere: 
* Explanation: Adds a sphere.
* Interface: float mass(No default value), float additionToRadius(Default value 0)
*
* addCylinder: NOT YET TESTED!!! Need 3d shape loading to perform proper testing.
* Explanation: Adds a cylinder. NOTE: I think the cylinder by default is created on its side(X axis goes trough the hole)
* Interface: float mass(No default value), float additionToDiameter (Default value 0), float additionToHeight (Default value 0)
*
* setRotation: Allows or restricts rotation on a given axis.
* Value of 1 allows rotation, value of 0 restricts rotation. By default bodies have allowed rotation on all 3 axes
* Interface: btVector &rotFlags(No default value)
*
* setMovement: Allows or restricts movement on a given axis.
* Value of 1 allows movement, value of 0 restricts movement. By default bodies have allowed movement on all 3 axes
* Interface: btVector &movFlags(No default value)
*
* setGravity: 
* Explanation: Allows to set the gravity for a given body. By default gravity is set to (0, -10, 0)
* Interface: btVector3 &g(No default value)
*
* setBounciness:
* Explanation: Allows to set the bounce property of the given object. By default, bounciness is set to  1 for plane and to 0 for everything else
* Interface: float bounce(No default value)
*
*/


class CollisionComponent : public IComponent
{
public:
	CollisionComponent(Entity entity);
	~CollisionComponent();

	void Refresh();

	bulletObject *getBodyStructure() {return m_pBody;}
	void updateHitboxPosition(glm::vec3 vec);
	void updateHitboxAngle(glm::quat q);
	void toggleHitboxView();

	void addPlane();
	void addBox(float mass, const btVector3 &additionToDimensions = btVector3(0, 0, 0));
	void addSphere(float mass, float additionToRadius = 0);
	void addCylinder(float mass, float additionToDiameter = 0, float additionToHeight = 0);

	void setRotation(btVector3 &rotFlags) { m_pBody->rotationFlags = rotFlags; }
	void setMovement(btVector3 &movFlags) { m_pBody->movementFlags = movFlags; }
	void setGravity(btVector3 &g) { m_pBody->gravity = g; }
	void setBounciness(float bounce) { m_pBody->body->setRestitution(bounce); }
	

private:
	DrawComponent * m_pDraw;
	MovableComponent* m_pMover;
	TransformComponent* m_pTransform;
	Entity m_HitboxEntity;
	bool m_IsCollisionViewEnabled;
	bulletObject * m_pBody;
};
