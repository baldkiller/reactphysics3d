/********************************************************************************
* ReactPhysics3D physics library, http://code.google.com/p/reactphysics3d/      *
* Copyright (c) 2010-2012 Daniel Chappuis                                       *
*********************************************************************************
*                                                                               *
* This software is provided 'as-is', without any express or implied warranty.   *
* In no event will the authors be held liable for any damages arising from the  *
* use of this software.                                                         *
*                                                                               *
* Permission is granted to anyone to use this software for any purpose,         *
* including commercial applications, and to alter it and redistribute it        *
* freely, subject to the following restrictions:                                *
*                                                                               *
* 1. The origin of this software must not be misrepresented; you must not claim *
*    that you wrote the original software. If you use this software in a        *
*    product, an acknowledgment in the product documentation would be           *
*    appreciated but is not required.                                           *
*                                                                               *
* 2. Altered source versions must be plainly marked as such, and must not be    *
*    misrepresented as being the original software.                             *
*                                                                               *
* 3. This notice may not be removed or altered from any source distribution.    *
*                                                                               *
********************************************************************************/

#ifndef QUATERNION_H
#define QUATERNION_H

// Libraries
#include <cmath>
#include "Vector3.h"
#include "Matrix3x3.h"
#include "../decimal.h"

// ReactPhysics3D namespace
namespace reactphysics3d {

/*  -------------------------------------------------------------------
    Class Quaternion :
        This class represents a quaternion. We use the notation :
        q = (x*i, y*j, z*k, w) to represent a quaternion.
    -------------------------------------------------------------------
*/
class Quaternion {
    private :
        decimal x;      // Component x of the quaternion
        decimal y;      // Component y of the quaternion
        decimal z;      // Component z of the quaternion
        decimal w;      // Component w of the quaternion

    public :
        Quaternion();                                                   // Constructor
        Quaternion(decimal x, decimal y, decimal z, decimal w);         // Constructor with arguments
        Quaternion(decimal w, const Vector3& v);                        // Constructor with the component w and the vector v=(x y z)
        Quaternion(const Quaternion& quaternion);                       // Copy-constructor
        Quaternion(const Matrix3x3& matrix);                            // Create a unit quaternion from a rotation matrix
        ~Quaternion();                                                  // Destructor
        decimal getX() const;                                           // Return the component x of the quaternion
        decimal getY() const;                                           // Return the component y of the quaternion
        decimal getZ() const;                                           // Return the component z of the quaternion
        decimal getW() const;                                           // Return the component w of the quaternion
        void setX(decimal x);                                           // Set the value x
        void setY(decimal y);                                           // Set the value y
        void setZ(decimal z);                                           // Set the value z
        void setW(decimal w);                                           // Set the value w
        Vector3 vectorV() const;                                        // Return the vector v=(x y z) of the quaternion
        decimal length() const;                                         // Return the length of the quaternion
        Quaternion getUnit() const;                                     // Return the unit quaternion
        Quaternion getConjugate() const;                                // Return the conjugate quaternion
        Quaternion getInverse() const;                                  // Return the inverse of the quaternion
        Matrix3x3 getMatrix() const;                                    // Return the orientation matrix corresponding to this quaternion
        static Quaternion identity();                                   // Return the identity quaternion
        decimal dot(const Quaternion& quaternion) const;                // Dot product between two quaternions
        void getRotationAngleAxis(decimal& angle, Vector3& axis) const; // Compute the rotation angle (in radians) and the axis
        static Quaternion slerp(const Quaternion& quaternion1,
                                const Quaternion& quaternion2, decimal t);   // Compute the spherical linear interpolation between two quaternions

        // --- Overloaded operators --- //
        Quaternion operator+(const Quaternion& quaternion) const;       // Overloaded operator for the addition
        Quaternion operator-(const Quaternion& quaternion) const;       // Overloaded operator for the substraction
        Quaternion operator*(decimal nb) const;                         // Overloaded operator for the multiplication with a constant
        Quaternion operator*(const Quaternion& quaternion) const;       // Overloaded operator for the multiplication
        Quaternion& operator=(const Quaternion& quaternion);            // Overloaded operator for assignment
        bool operator==(const Quaternion& quaternion) const;            // Overloaded operator for equality condition
};

// --- Inline functions --- //

// Get the value x (inline)
inline decimal Quaternion::getX() const {
    return x;
}

// Get the value y (inline)
inline decimal Quaternion::getY() const {
    return y;
}

// Get the value z (inline)
inline decimal Quaternion::getZ() const {
    return z;
}

// Get the value w (inline)
inline decimal Quaternion::getW() const {
    return w;
}

// Set the value x (inline)
inline void Quaternion::setX(decimal x) {
    this->x = x;
}

// Set the value y (inline)
inline void Quaternion::setY(decimal y) {
    this->y = y;
}

// Set the value z (inline)
inline void Quaternion::setZ(decimal z) {
    this->z = z;
}

// Set the value w (inline)
inline void Quaternion::setW(decimal w) {
    this->w = w;
}

// Return the vector v=(x y z) of the quaternion
inline Vector3 Quaternion::vectorV() const {
    // Return the vector v
    return Vector3(x, y, z);
}

// Return the length of the quaternion (inline)
inline decimal Quaternion::length() const {
    return sqrt(x*x + y*y + z*z + w*w);
}

// Return the unit quaternion
inline Quaternion Quaternion::getUnit() const {
    decimal lengthQuaternion = length();

    // Check if the length is not equal to zero
    assert (lengthQuaternion != 0.0);

    // Compute and return the unit quaternion
    return Quaternion(x/lengthQuaternion, y/lengthQuaternion, z/lengthQuaternion, w/lengthQuaternion);
}

// Return the identity quaternion
inline Quaternion Quaternion::identity() {
    return Quaternion(0.0, 0.0, 0.0, 1.0);
}

// Return the conjugate of the quaternion (inline)
inline Quaternion Quaternion::getConjugate() const {
    return Quaternion(-x, -y, -z, w);
}

// Return the inverse of the quaternion (inline)
inline Quaternion Quaternion::getInverse() const {
    decimal lengthQuaternion = length();
    lengthQuaternion = lengthQuaternion * lengthQuaternion;

    assert (lengthQuaternion != 0.0);

    // Compute and return the inverse quaternion
    return Quaternion(-x/lengthQuaternion, -y/lengthQuaternion, -z/lengthQuaternion, w/lengthQuaternion);
}

// Scalar product between two quaternions
inline decimal Quaternion::dot(const Quaternion& quaternion) const {
    return (x*quaternion.x + y*quaternion.y + z*quaternion.z + w*quaternion.w);
}

// Overloaded operator for the addition of two quaternions
inline Quaternion Quaternion::operator+(const Quaternion& quaternion) const {
    // Return the result quaternion
    return Quaternion(x + quaternion.x, y + quaternion.y, z + quaternion.z, w + quaternion.w);
}

// Overloaded operator for the substraction of two quaternions
inline Quaternion Quaternion::operator-(const Quaternion& quaternion) const {
    // Return the result of the substraction
    return Quaternion(x-quaternion.x, y - quaternion.y, z - quaternion.z, w - quaternion.w);
}

// Overloaded operator for the multiplication with a constant
inline Quaternion Quaternion::operator*(decimal nb) const {
    // Return the result
    return Quaternion(nb*x, nb*y, nb*z, nb*w);
}

// Overloaded operator for the multiplication of two quaternions
inline Quaternion Quaternion::operator*(const Quaternion& quaternion) const {
    // Return the result of the multiplication
    return Quaternion(w*quaternion.w - vectorV().dot(quaternion.vectorV()), w*quaternion.vectorV()+quaternion.w*vectorV() + vectorV().cross(quaternion.vectorV()));
}

// Overloaded operator for the assignment
inline Quaternion& Quaternion::operator=(const Quaternion& quaternion) {
    // Check for self-assignment
    if (this != &quaternion) {
        x = quaternion.x;
        y = quaternion.y;
        z = quaternion.z;
        w = quaternion.w;
    }

    // Return this quaternion
    return *this;
}

// Overloaded operator for equality condition
inline bool Quaternion::operator==(const Quaternion& quaternion) const {
    return (x == quaternion.x && y == quaternion.y && z == quaternion.z && w == quaternion.w);
}

} // End of the ReactPhysics3D namespace

#endif
