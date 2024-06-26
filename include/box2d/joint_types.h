// SPDX-FileCopyrightText: 2023 Erin Catto
// SPDX-License-Identifier: MIT

#pragma once

#include "types.h"

/// Joint type enumeration
///
/// This is useful because all joint types use b2JointId and sometimes you
/// want to get the type of a joint.
/// @ingroup joint
typedef enum b2JointType
{
	b2_distanceJoint,
	b2_motorJoint,
	b2_mouseJoint,
	b2_prismaticJoint,
	b2_revoluteJoint,
	b2_weldJoint,
	b2_wheelJoint,
} b2JointType;

/// Distance joint definition
///
/// This requires defining an anchor point on both
/// bodies and the non-zero distance of the distance joint. The definition uses
/// local anchor points so that the initial configuration can violate the
/// constraint slightly. This helps when saving and loading a game.
/// @ingroup distance_joint
typedef struct b2DistanceJointDef
{
	/// The first attached body
	b2BodyId bodyIdA;

	/// The second attached body
	b2BodyId bodyIdB;

	/// The local anchor point relative to bodyA's origin
	b2Vec2 localAnchorA;

	/// The local anchor point relative to bodyB's origin
	b2Vec2 localAnchorB;

	/// The rest length of this joint. Clamped to a stable minimum value.
	float length;

	/// Enable the distance constraint to behave like a spring. If false
	///	then the distance joint will be rigid, overriding the limit and motor.
	bool enableSpring;

	/// The spring linear stiffness Hertz, cycles per second
	float hertz;

	/// The spring linear damping ratio, non-dimensional
	float dampingRatio;

	/// Enable/disable the joint limit
	bool enableLimit;

	/// Minimum length. Clamped to a stable minimum value.
	float minLength;

	/// Maximum length. Must be greater than or equal to the minimum length.
	float maxLength;

	/// Enable/disable the joint motor
	bool enableMotor;

	/// The maximum motor force, usually in newtons
	float maxMotorForce;

	/// The desired motor speed, usually in meters per second
	float motorSpeed;

	/// Set this flag to true if the attached bodies should collide
	bool collideConnected;

	/// User data pointer
	void* userData;

} b2DistanceJointDef;

/// Use this to initialize your joint definition
/// @ingroup distance_joint
B2_API b2DistanceJointDef b2DefaultDistanceJointDef();

/// A motor joint is used to control the relative motion between two bodies
///
/// A typical usage is to control the movement of a dynamic body with respect to the ground.
/// @ingroup motor_joint
typedef struct b2MotorJointDef
{
	/// The first attached body
	b2BodyId bodyIdA;

	/// The second attached body
	b2BodyId bodyIdB;

	/// Position of bodyB minus the position of bodyA, in bodyA's frame
	b2Vec2 linearOffset;

	/// The bodyB angle minus bodyA angle in radians
	float angularOffset;

	/// The maximum motor force in newtons
	float maxForce;

	/// The maximum motor torque in newton-meters
	float maxTorque;

	/// Position correction factor in the range [0,1]
	float correctionFactor;

	/// Set this flag to true if the attached bodies should collide
	bool collideConnected;

	/// User data pointer
	void* userData;

} b2MotorJointDef;

/// Use this to initialize your joint definition
/// @ingroup motor_joint
B2_API b2MotorJointDef b2DefaultMotorJointDef();

/// A mouse joint is used to make a point on a body track a specified world point.
///
/// This a soft constraint and allows the constraint to stretch without
/// applying huge forces. This also applies rotation constraint heuristic to improve control.
/// @ingroup mouse_joint
typedef struct b2MouseJointDef
{
	/// The first attached body.
	b2BodyId bodyIdA;

	/// The second attached body.
	b2BodyId bodyIdB;

	/// The initial target point in world space
	b2Vec2 target;

	/// Stiffness in hertz
	float hertz;

	/// Damping ratio, non-dimensional
	float dampingRatio;

	/// Maximum force, typically in newtons
	float maxForce;

	/// Set this flag to true if the attached bodies should collide.
	bool collideConnected;

	/// User data pointer
	void* userData;

} b2MouseJointDef;

/// Use this to initialize your joint definition
/// @ingroup mouse_joint
B2_API b2MouseJointDef b2DefaultMouseJointDef();

/// Prismatic joint definition
///
/// This requires defining a line of motion using an axis and an anchor point.
/// The definition uses local anchor points and a local axis so that the initial
/// configuration can violate the constraint slightly. The joint translation is zero
/// when the local anchor points coincide in world space.
/// @ingroup prismatic_joint
typedef struct b2PrismaticJointDef
{
	/// The first attached body
	b2BodyId bodyIdA;

	/// The second attached body
	b2BodyId bodyIdB;

	/// The local anchor point relative to bodyA's origin
	b2Vec2 localAnchorA;

	/// The local anchor point relative to bodyB's origin
	b2Vec2 localAnchorB;

	/// The local translation unit axis in bodyA
	b2Vec2 localAxisA;

	/// The constrained angle between the bodies: bodyB_angle - bodyA_angle
	float referenceAngle;

	/// Enable a linear spring along the prismatic joint axis
	bool enableSpring;

	/// The spring stiffness Hertz, cycles per second
	float hertz;

	/// The spring damping ratio, non-dimensional
	float dampingRatio;
	
	/// Enable/disable the joint limit
	bool enableLimit;

	/// The lower translation limit
	float lowerTranslation;

	/// The upper translation limit
	float upperTranslation;

	/// Enable/disable the joint motor
	bool enableMotor;

	/// The maximum motor force, typically in newtons
	float maxMotorForce;

	/// The desired motor speed, typically in meters per second
	float motorSpeed;

	/// Set this flag to true if the attached bodies should collide
	bool collideConnected;

	/// User data pointer
	void* userData;
} b2PrismaticJointDef;

/// Use this to initialize your joint definition
/// @ingroupd prismatic_joint
B2_API b2PrismaticJointDef b2DefaultPrismaticJointDef();

/// Revolute joint definition
/// 
/// This requires defining an anchor point where the bodies are joined.
/// The definition uses local anchor points so that the
/// initial configuration can violate the constraint slightly. You also need to
/// specify the initial relative angle for joint limits. This helps when saving
/// and loading a game.
/// The local anchor points are measured from the body's origin
/// rather than the center of mass because:
/// 1. you might not know where the center of mass will be
/// 2. if you add/remove shapes from a body and recompute the mass, the joints will be broken
/// @ingroup revolute_joint
typedef struct b2RevoluteJointDef
{
	/// The first attached body
	b2BodyId bodyIdA;

	/// The second attached body
	b2BodyId bodyIdB;

	/// The local anchor point relative to bodyA's origin
	b2Vec2 localAnchorA;

	/// The local anchor point relative to bodyB's origin
	b2Vec2 localAnchorB;

	/// The bodyB angle minus bodyA angle in the reference state (radians).
	/// This defines the zero angle for the joint limit.
	float referenceAngle;

	/// Enable a rotational spring on the revolute hinge axis
	bool enableSpring;

	/// The spring stiffness Hertz, cycles per second
	float hertz;

	/// The spring damping ratio, non-dimensional
	float dampingRatio;
	
	/// A flag to enable joint limits
	bool enableLimit;

	/// The lower angle for the joint limit in radians
	float lowerAngle;

	/// The upper angle for the joint limit in radians
	float upperAngle;

	/// A flag to enable the joint motor
	bool enableMotor;

	/// The maximum motor torque, typically in newton-meters
	float maxMotorTorque;

	/// The desired motor speed in radians per second
	float motorSpeed;

	/// Scale the debug draw
	float drawSize;

	/// Set this flag to true if the attached bodies should collide
	bool collideConnected;

	/// User data pointer
	void* userData;
} b2RevoluteJointDef;

/// Use this to initialize your joint definition.
/// @ingroup revolute_joint
B2_API b2RevoluteJointDef b2DefaultRevoluteJointDef();

/// Weld joint definition
///
/// A weld joint connect to bodies together rigidly. This constraint provides springs to mimic
///	soft-body simulation.
/// @note The approximate solver in Box2D cannot hold many bodies together rigidly
/// @ingroup weld_joint
typedef struct b2WeldJointDef
{
	/// The first attached body
	b2BodyId bodyIdA;

	/// The second attached body
	b2BodyId bodyIdB;

	/// The local anchor point relative to bodyA's origin
	b2Vec2 localAnchorA;

	/// The local anchor point relative to bodyB's origin
	b2Vec2 localAnchorB;

	/// The bodyB angle minus bodyA angle in the reference state (radians)
	float referenceAngle;

	/// Linear stiffness expressed as Hertz (cycles per second). Use zero for maximum stiffness.
	float linearHertz;

	/// Angular stiffness as Hertz (cycles per second). Use zero for maximum stiffness.
	float angularHertz;

	/// Linear damping ratio, non-dimensional. Use 1 for critical damping.
	float linearDampingRatio;

	/// Linear damping ratio, non-dimensional. Use 1 for critical damping.
	float angularDampingRatio;

	/// Set this flag to true if the attached bodies should collide
	bool collideConnected;

	/// User data pointer
	void* userData;
} b2WeldJointDef;

/// Use this to initialize your joint definition
/// @ingroup weld_joint
B2_API b2WeldJointDef b2DefaultWeldJointDef();

/// Wheel joint definition
///
/// This requires defining a line of motion using an axis and an anchor point.
/// The definition uses local  anchor points and a local axis so that the initial
/// configuration can violate the constraint slightly. The joint translation is zero
/// when the local anchor points coincide in world space.
/// @ingroup wheel_joint
typedef struct b2WheelJointDef
{
	/// The first attached body
	b2BodyId bodyIdA;

	/// The second attached body
	b2BodyId bodyIdB;

	/// The local anchor point relative to bodyA's origin
	b2Vec2 localAnchorA;

	/// The local anchor point relative to bodyB's origin
	b2Vec2 localAnchorB;

	/// The local translation unit axis in bodyA
	b2Vec2 localAxisA;

	/// Enable a linear spring along the local axis
	bool enableSpring;
	
	/// Spring stiffness in Hertz
	float hertz;

	/// Spring damping ratio, non-dimensional
	float dampingRatio;

	/// Enable/disable the joint linear limit
	bool enableLimit;

	/// The lower translation limit
	float lowerTranslation;

	/// The upper translation limit
	float upperTranslation;

	/// Enable/disable the joint rotational motor
	bool enableMotor;

	/// The maximum motor torque, typically in newton-meters
	float maxMotorTorque;

	/// The desired motor speed in radians per second
	float motorSpeed;

	/// Set this flag to true if the attached bodies should collide
	bool collideConnected;

	/// User data pointer
	void* userData;
} b2WheelJointDef;

/// Use this to initialize your joint definition
/// @ingroup wheel_joint
B2_API b2WheelJointDef b2DefaultWheelJointDef();
