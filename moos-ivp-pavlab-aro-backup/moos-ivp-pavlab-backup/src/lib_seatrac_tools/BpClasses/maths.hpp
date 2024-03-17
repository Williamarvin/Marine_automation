/*==============================================================================

==============================================================================*/
//Prevent multiple inclusions of this file
#ifndef MATHS_HPP
#define MATHS_HPP

//Include the system maths library
//#include <math.h>

//Include common type definitions and macros
#include "common.h"

//==============================================================================
//Mathematical Definitions
//==============================================================================
//#define PI 		3.14159265358979
#define PI			3.1415926535897932384626433832795
#define TWO_PI		(PI * 2)
#define HALF_PI		(PI / 2)

#define RAD_TO_DEG	(180.0 / PI)	/* Multiply radians by this to get degrees */
#define DEG_TO_RAD  (PI / 180.0)	/* Multiply degrees by this to get radians */

//==============================================================================
//Definitions...
//==============================================================================
//Pforward delcare the structs and classes
template <typename T> struct TPoint;
template <typename T> struct TCartesian;

//------------------------------------------------------------------------------
/*! Define a structure that holds a generic 2D cartesian encoded value */
template <typename T>
struct TPoint {
	union {
		struct {
			T X;
			T Y;
		};
		struct {
			T Easting;
			T Northing;
		};
	};

	//Constructors
	TPoint() {};
	explicit TPoint(const T value) : X(value), Y(value) {};
	explicit TPoint(const T x, const T y) : X(x), Y(y) {};
	explicit TPoint(const TCartesian<T>& value);

	//Methods
	inline void SetValue(const T value) { X = value; Y = value; };
	inline void SetValue(const T x, const T y) { X = x; Y = y; };
};

//------------------------------------------------------------------------------
/*! Define a structure that holds a generic 3D cartesian encoded value.
The type impliments the ISerializable interface, allowing it to be packed into a
stream.
*/
template <typename T>
struct TCartesian {
	union {
		struct {
			T X;
			T Y;
			T Z;
		};
		struct {
			T Easting;
			T Northing;
			union {
				T Height;	//NB: It is up the the user to decide the 'signs' of Height or Depth - but names should be consistent
				T Depth;
			};
		};
	};

	//Constructors
	TCartesian() {};
	explicit TCartesian(const T value) : X(value), Y(value), Z(value) {};
	explicit TCartesian(const T x, const T y, const T z) : X(x), Y(y), Z(z) {};
	explicit TCartesian(const TPoint<T>& value, const T z = T(0));

	inline void SetValue(const T value) { X = value; Y = value; Z = value; };
	inline void SetValue(const T x, const T y, const T z) { X = x; Y = y; Z = z; };
};

typedef TCartesian<uint8> TCartesianU8;
typedef TCartesianU8* PCartesianU8;

typedef TCartesian<int16> TCartesianI16;
typedef TCartesianI16* PCartesianI16;

typedef TCartesian<int32> TCartesianI32;
typedef TCartesianI32* PCartesianI32;

typedef TCartesian<float> TCartesianF;
typedef TCartesianF* PCartesianF;

typedef TCartesian<double> TCartesianD;
typedef TCartesianD* PCartesianD;

//------------------------------------------------------------------------------
/*! Define an attitude of a platform (may be in degrees or radians).
The type impliments the ISerializable interface, allowing it to be packed into a
stream.
The attitude may be treated as Euler angles if required.
*/
template <typename T>
struct TAttitude {
	T Yaw;
	T Pitch;
	T Roll;

	//Constructors
	TAttitude() {};
	explicit TAttitude(const T value) : Yaw(value), Pitch(value), Roll(value) {};
	explicit TAttitude(const T y, const T p, const T r) : Yaw(y), Pitch(p), Roll(r) {};

	//Methods
	inline void DegToRad();
	inline void DegToRad(TAttitude<T>& attitude);
	inline void RadToDeg();
	inline void RadToDeg(TAttitude<T>& attitude);

};

typedef TAttitude<int16> TAttitudeI16;
typedef TAttitudeI16* PAttitudeI16;

typedef TAttitude<float> TAttitudeF;
typedef TAttitudeF* PAttitudeF;

typedef TAttitude<double> TAttitudeD;
typedef TAttitudeD* PAttitudeD;

//------------------------------------------------------------------------------
/*! Define a structre to hold Euler Angles (may be in degrees or radians)
How the Euler angles are interprited is up to the application

template <typename T>
struct TEuler {
	union {
		T Alpha;
		T Phi;
	};
	union {
		T Beta;
		T Theta;
	};
	union {
		T Gamma;
		T Psi;
	};

	//Constructors
	TEuler() {};
	explicit TEuler(const T value) : Alpha(value), Beta(value), Gamma(value) {};
	explicit TEuler(const T a, const T b, const T g) : Alpha(a), Beta(b), Gamma(g) {};

	//Methods
	inline void DegToRad();
	inline void DegToRad(TEuler<T>& euler);
	inline void RadToDeg();
	inline void RadToDeg(TEuler<T>& euler);
};

typedef TEuler<float> TEulerF;
typedef TEulerF* PEulerF;

typedef TEuler<double> TEulerD;
typedef TEulerD* PEulerD;
*/

//------------------------------------------------------------------------------
/*! Define a structure for describling an angle from the centre of a sphere */
template <typename T>
struct TSphericalAngle {
	T Azimuth;		/*!< Phi - The anticlockwise angle between the positive x-axis and the projection of the vector onto the xy-plane. */
	T Elevation;	/*!< Theta - The angle above (positive) or below the xy-plane (not the polar angle, sometimes called 'Inclination'!). */
};

typedef TSphericalAngle<float> TSphericalAngleF;
typedef TSphericalAngleF* PSphericalAngleF;

typedef TSphericalAngle<double> TSphericalAngleD;
typedef TSphericalAngleD* PSphericalAngleD;

//------------------------------------------------------------------------------
/*! Define a structure to hold a Quarternion value */
template <typename T>
struct TQuarternion {
	union {
		struct {
			T Q0;
			T Q1;
			T Q2;
			T Q3;
		};
		struct {
			T W;
			T X;
			T Y;
			T Z;
		};
		T Q[4];	//Declare an array of four quarternion terms (Scalar/Angular, VectorX, VectorY, and VectorZ)
	};

	//Constructor
	TQuarternion() {};
	explicit TQuarternion(T& q0, T& q1, T& q2, T& q3) : Q0(q0), Q1(q1), Q2(q2), Q3(q3) {};

	//Methods
	inline void SetValue(T& q0, T& q1, T& q2, T& q3) { Q0=q0; Q1=q1; Q2=q2; Q3=q3; };
};

typedef TQuarternion<float> TQuarternionF;
typedef TQuarternionF* PQuarternionF;

typedef TQuarternion<double> TQuarternionD;
typedef TQuarternionD* PQuarternionD;

/*!-----------------------------------------------------------------------------
Macro that allows quick checking that a value lies inclusively between
the specified min and max values.
This effectively specifies a "Closed Interval" range (see "http://en.wikipedia.org/wiki/Interval_(mathematics)")
*/
#define MATHS_RANGE_CHECK(VALUE, VALMIN, VALMAX)	(((VALUE) >= (VALMIN)) && ((VALUE) <= (VALMAX)))

/*!-----------------------------------------------------------------------------
Macro that allows quick clipping of a value to the limits of the specified
range
*/
#define MATHS_RANGE_CLIP(VALUE, VALMIN, VALMAX)		{ \
	if((VALUE) < (VALMIN)) \
		VALUE = (VALMIN); \
	else if((VALUE) > (VALMAX)) \
		VALUE = (VALMAX); \
}

/*!-----------------------------------------------------------------------------
Macro that allows quick clipping of a value to the limits of the specified
range
*/
#define MATHS_RANGE_CLIPMAX(VALUE, VALMAX)		{ \
	if((VALUE) > (VALMAX)) \
		VALUE = (VALMAX); \
}

/*!-----------------------------------------------------------------------------
Macro that performs a cyclic modulus function on a value between a min
and max values.
Note that the value will never equal the max value - i.e.
	MATHS_RANGE_MODULUS(3, 5, 8) = 7
	MATHS_RANGE_MODULUS(-270.0, -180.0, 180.0) = 90.0;
	MATHS_RANGE_MODULUS(360.0, 0.0, 360.0) = 360.0;
*/
#define MATHS_RANGE_MODULUS(VALUE, VALMIN, VALMAX)	{ \
	while(VALUE < VALMIN) \
		VALUE += ((VALMAX) - (VALMIN)); \
	while(VALUE >= VALMAX) \
		VALUE -= ((VALMAX) - (VALMIN)); \
}

//==============================================================================
//Class Implimentation...
//==============================================================================
//TPoint
//==============================================================================
/*!-----------------------------------------------------------------------------
Constructor that assigns a Cartesian 3D value to a Point 2D value, discarding the Z-axis value
*/
template <typename T>
TPoint<T>::TPoint(const TCartesian<T>& value) :
	X(value.X), Y(value.Y)
{
}

//==============================================================================
//TCartesian
//==============================================================================
/*!-----------------------------------------------------------------------------
Constructor that assigns a Point 2D value to a Cartesian 3D value, with option
to load a value into the Z-axis.
*/
template <typename T>
TCartesian<T>::TCartesian(const TPoint<T>& value, const T z) :
	X(value.X), Y(value.Y), Z(z)
{
}

//==============================================================================
//TAttitude
//==============================================================================
/*!-----------------------------------------------------------------------------
Function that converts the attitudes values from degrees to radians
*/
template <typename T>
void TAttitude<T>::DegToRad()
{
	this->DegToRad(*this);
}

/*!-----------------------------------------------------------------------------
Function that converts the attitudes values from degrees to radians
@param	attitude	Reference to an attitude to copy and convert into radians
*/
template <typename T>
void TAttitude<T>::DegToRad(TAttitude<T>& attitude)
{
	this->Pitch = attitude.Pitch * DEG_TO_RAD;
	this->Roll = attitude.Roll * DEG_TO_RAD;
	this->Yaw = attitude.Yaw * DEG_TO_RAD;
}

/*!-----------------------------------------------------------------------------
Function that converts the attitudes values from radians to degrees
*/
template <typename T>
void TAttitude<T>::RadToDeg()
{
	this->RadToDeg(*this);
}

/*!-----------------------------------------------------------------------------
Function that converts the attitudes values from radians to degrees
@param	attitude	Reference to an attitude to copy and convert into degrees
*/
template <typename T>
void TAttitude<T>::RadToDeg(TAttitude<T>& attitude)
{
	this->Pitch = attitude.Pitch * RAD_TO_DEG;
	this->Roll = attitude.Roll * RAD_TO_DEG;
	this->Yaw = attitude.Yaw * RAD_TO_DEG;
}

//==============================================================================
//TEuler
//==============================================================================
/*!-----------------------------------------------------------------------------
Function that converts the euler angle values from degrees to radians

template <typename T>
void TEuler<T>::DegToRad()
{
	this->DegToRad(*this);
}
*/

/*!-----------------------------------------------------------------------------
Function that converts the euler angle values from degrees to radians
@param	euler	Reference to an euler angle to copy and convert into radians

template <typename T>
void TEuler<T>::DegToRad(TEuler<T>& euler)
{
	this->Alpha = euler.Alpha * DEG_TO_RAD;	// Phi
	this->Beta = euler.Beta * DEG_TO_RAD;	// Theta
	this->Gamma = euler.Gamma * DEG_TO_RAD;	// Psi
}
*/

/*!-----------------------------------------------------------------------------
Function that converts the euler angle values from radians to degrees

template <typename T>
void TEuler<T>::RadToDeg()
{
	this->RadToDeg(*this);
}
*/

/*!-----------------------------------------------------------------------------
Function that converts the euler angle values from radians to degrees
@param	attitude	Reference to an euler angle to copy and convert into degrees

template <typename T>
void TEuler<T>::RadToDeg(TEuler<T>& euler)
{
	this->Alpha = euler.Alpha * RAD_TO_DEG;	// Phi
	this->Beta = euler.Beta * RAD_TO_DEG;	// Theta
	this->Gamma = euler.Gamma * RAD_TO_DEG;	// Psi
}
*/


//==============================================================================
//CMaths
//==============================================================================
//------------------------------------------------------------------------------
/*!
Define a class that provide mathematical helper functions
*/
class CMaths {
	public:
		static inline float DegreesToRadians(float angle);
		static inline double DegreesToRadians(double angle);

		static float Fraction(float value);
		static double Fraction(double value); // { return value - (double)((int32)value); }

		static inline float InverseSqrt(float number);

		static inline float NormaliseDegrees(float angle);
		static inline double NormaliseDegrees(double angle);
		static inline float NormaliseRadians(float angle);
		static inline double NormaliseRadians(double angle);

		static inline float RadiansToDegrees(float angle);
		static inline double RadiansToDegrees(double angle);

		/* See "MATHS_RANGE_XXXX" macros
		template <typename T>
		static inline void RangeCyclic(T* value, T max);

		template <typename T>
		static inline void RangeLimit(T* value, T min, T max);

		template <typename T>
		static inline bool RangeValidate(T value, T min, T max);
		*/

		static inline float RolloverDegrees(float angle);
		static inline double RolloverDegrees(double angle);
		static inline float RolloverRadians(float angle);
		static inline double RolloverRadians(double angle);

		static int32 Round(float value);
		static int32 Round(double value);

		static inline int32 RoundMultipleUp(int32 value, int32 multiple);

		static inline float Sign(float value);
		static inline double Sign(double value);
};

//==============================================================================
#endif
