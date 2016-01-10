/**
 \file Color3.h
 
 Color class
 
 \maintainer Morgan McGuire, http://graphics.cs.williams.edu
 \cite Portions based on Dave Eberly's Magic Software Library
      at <A HREF="http://www.magic-software.com">http://www.magic-software.com</A>
 
 \created 2001-06-02
 \edited  2013-10-07

 Copyright 2000-2015, Morgan McGuire.
 All rights reserved.
 */

#ifndef G3D_Color3_h
#define G3D_Color3_h

#include "G3D/platform.h"
#include "G3D/DoNotInitialize.h"
#include "G3D/g3dmath.h"
#include "G3D/HashTrait.h"
#include "G3D/Color1.h"
#include "G3D/G3DString.h"

namespace G3D {
class Any;

/**
 Do not subclass-- this implementation makes assumptions about the
 memory layout.
 */
class Color3 {
private:
    // Hidden operators
    bool operator<(const Color3&) const;
    bool operator>(const Color3&) const;
    bool operator<=(const Color3&) const;
    bool operator>=(const Color3&) const;

public:
    /**
     \brief Initializes to all zero.
     */
    Color3() : r(0), g(0), b(0) {}

    Color3(DoNotInitialize dni) {}

    bool nonZero() const {
        return (r != 0) || (g != 0) || (b != 0);
    }

    /** \param any Must be in one of the following forms: 
        - Color3(#, #, #)
        - Color3(#)
        - Color3::fromARGB(#)
        - Color3::fromASRGB(#)
        - Color3{r = #, g = #, b = #)
        - Color3::one()
        - Color3::zero()

        In the current implementation, G3D::Power3, G3D::Radiance3,
        and G3D::Irradiance3 are typedefs for Color3, so Color3
        accepts "Power3" and "Radiance3" as a prefixes as well, e.g.,
        Power3(1,0,0).
        */
    explicit Color3(const Any& any);
    
    Color3& operator=(const Any& a);

    /** Converts the Color3 to an Any. */
    Any toAny() const;

    explicit Color3(class BinaryInput& bi);

    Color3(float r, float g, float b);

    /** \brief Initializes all channels to \a v */
    explicit Color3(float v) : r(v), g(v), b(v) {}

    explicit Color3(const class Vector3& v);
    
    explicit Color3(const float value[3]);

    /** Returns this color */
    const Color3& rgb() const {
        return *this;
    }

    /**
     Initialize from another color.
     */
    Color3 (const Color3& other);

    Color3 (const class Color3unorm8& other);

    inline bool isZero() const {
        return (r == 0.0f) && (g == 0.0f) && (b == 0.0f);
    }

    inline bool isOne() const {
        return (r == 1.0f) && (g == 1.0f) && (b == 1.0f);
    }

    bool isFinite() const;

    /**
     Initialize from an HTML-style color (e.g. 0xFF0000 == RED)
     */
    static Color3 fromARGB(uint32);

    /**
     Initialize from an HTML-style color (e.g. 0xFF0000 == RED) by converting from sRGB to RGB.
     The alpha channel is linear.
     */
    static Color3 fromASRGB(uint32);

    /** Returns one of the color wheel colors (e.g. RED, GREEN, CYAN).
        Does not include white, black, or gray. */
    static const Color3& wheelRandom();

    /** Generate colors according to the ANSI color set, mod 16.
     \sa pastelMap */
    static Color3 ansiMap(uint32 i);

    /**
       Generate colors using a hash such that adjacent values
       are unlikely to have similar colors.

       Useful for rendering with
       stable but arbitrary colors, e.g., when debugging a mesh
       algorithm. 

       \sa ansiMap
     */
    static Color3 pastelMap(uint32 i);

    /**
     * Channel value.
     */
    float r, g, b;

    void serialize(class BinaryOutput& bo) const;
    void deserialize(class BinaryInput& bi);

    // access vector V as V[0] = V.r, V[1] = V.g, V[2] = V.b
    //
    // WARNING.  These member functions rely on
    // (1) Color3 not having virtual functions
    // (2) the data packed in a 3*sizeof(float) memory block
    const float& operator[] (int i) const;
    float& operator[] (int i);

    // assignment and comparison
    Color3& operator= (const Color3& rkVector);
    bool operator== (const Color3& rkVector) const;
    bool operator!= (const Color3& rkVector) const;
    size_t hashCode() const;

    // arithmetic operations
    Color3 operator+ (const Color3& rkVector) const;
    Color3 operator- (const Color3& rkVector) const;
    inline Color3 operator* (float s) const {
        return Color3(r * s, g * s, b * s);
    }
    inline Color3 operator/ (const Color3& rkVector) const {
        return Color3(r / rkVector.r, g / rkVector.g, b / rkVector.b);
    }

    Color3 operator* (const Color3& rkVector) const;
    inline Color3 operator/ (float fScalar) const {
        return (*this) * (1.0f / fScalar);
    }
    
    Color3 operator- () const;

    // arithmetic updates
    Color3& operator+= (const Color3& rkVector);
    Color3& operator-= (const Color3& rkVector);
    Color3& operator*= (const Color3& rkVector);
    Color3& operator*= (float fScalar);
    Color3& operator/= (float fScalar);

    bool fuzzyEq(const Color3& other) const;
    bool fuzzyNe(const Color3& other) const;

    // vector operations
    float length () const;
    Color3 direction() const;
    float squaredLength () const;
    float dot (const Color3& rkVector) const;
    float unitize (float fTolerance = 1e-06);
    Color3 cross (const Color3& rkVector) const;
    Color3 unitCross (const Color3& rkVector) const;

    inline Color3 pow(const Color3& other) const {
        return Color3(::pow(r, other.r), ::pow(g, other.g), ::pow(b, other.b));
    }
    
    inline Color3 pow(float other) const {
        return Color3(::pow(r, other), ::pow(g, other), ::pow(b, other));
    }

    inline Color3 max(const Color3& other) const {
        return Color3(G3D::max(r, other.r), G3D::max(g, other.g), G3D::max(b, other.b));
    }

    inline Color3 min(const Color3& other) const {
        return Color3(G3D::min(r, other.r), G3D::min(g, other.g), G3D::min(b, other.b));
    }

    /** Smallest element */
    inline float min() const {
        return G3D::min(G3D::min(r, g), b);
    }

    /** Largest element */
    inline float max() const {
        return G3D::max(G3D::max(r, g), b);
    }

    inline Color3 lerp(const Color3& other, float a) const {
        return (*this) + (other - *this) * a; 

    }

    inline float sum() const {
        return r + g + b;
    }

    Color3 clamp(float low, float high) const {
        return Color3(G3D::clamp(r, low, high), G3D::clamp(g, low, high), G3D::clamp(b, low, high));
    }

    inline float average() const {
        return sum() / 3.0f;
    }

    /** Scales "saturation". Technically, this should be applied to only sRGB color space values. */
    Color3 scaleSaturation(float factor) const;

    /**
     *  Converts from HSV to RGB , note: toHSV(fromHSV(_hsv)) may not be _hsv, if it is at a grey point or black point.
     *  The components of _hsv should lie in the unit interval. 
     *  @cite Alvy Ray Smith SIGGRAPH 1978 "Color Gamut Transform Pairs"
     **/
    static Color3 fromHSV(const Vector3& _hsv);
    static Vector3 toHSV(const Color3& _rgb);
    
    /** Duplicates the matlab jet colormap maps [0,1] --> (r,g,b) where blue is close to  0 and red is close to 1. */
    static Color3 jetColorMap(const float& val);
    
    /** Returns colors with maximum saturation and value @param hue [0, 1]*/
    static Color3 rainbowColorMap(float hue);

    String toString() const;

    /** Random unit vector */
    static Color3 random();

    static inline Color3 neonGradient(float t) {
        return Color3(t * 1.3f + 0.1f, square(::fabsf(0.43f - t) * 1.7f), (1.0f - t) * 1.7f).clamp(0.0f, 1.0f);
    }

    // Special values.
    // Intentionally not inlined: see Matrix3::identity() for details.
    static const Color3& red();
    static const Color3& green();
    static const Color3& blue();
    static const Color3& purple();
    static const Color3& cyan();
    static const Color3& yellow();
    static const Color3& brown();
    static const Color3& orange();
    static const Color3& black();
    static const Color3& gray();
    static const Color3& white();

    static const Color3& zero();
    static const Color3& one();
	static const Color3& nan();

    inline Color3 bgr() const {
        return Color3(b, g, r);
    }
};

inline G3D::Color3 operator* (float s, const G3D::Color3& c) {
    return c * s;
}

inline G3D::Color3 operator* (G3D::Color1& s, const G3D::Color3& c) {
    return c * s.value;
}

inline G3D::Color3 operator* (const G3D::Color3& c, G3D::Color1& s) {
    return c * s.value;
}

inline G3D::Color3 operator/ (float s, const G3D::Color3& c) {
    return c * (1.0f/s);
}


//----------------------------------------------------------------------------

inline Color3::Color3(float fX, float fY, float fZ) {
    r = fX;
    g = fY;
    b = fZ;
}

//----------------------------------------------------------------------------
inline Color3::Color3(const float afCoordinate[3]) {
    r = afCoordinate[0];
    g = afCoordinate[1];
    b = afCoordinate[2];
}

//----------------------------------------------------------------------------
inline Color3::Color3 (const Color3& rkVector) {
    r = rkVector.r;
    g = rkVector.g;
    b = rkVector.b;
}

//----------------------------------------------------------------------------
inline float& Color3::operator[] (int i) {
    return ((float*)this)[i];
}

//----------------------------------------------------------------------------

inline const float& Color3::operator[] (int i) const {
    return ((float*)this)[i];
}

//----------------------------------------------------------------------------

inline bool Color3::fuzzyEq(const Color3& other) const {
    return G3D::fuzzyEq((*this - other).squaredLength(), 0);
}

//----------------------------------------------------------------------------

inline bool Color3::fuzzyNe(const Color3& other) const {
    return G3D::fuzzyNe((*this - other).squaredLength(), 0);
}


//----------------------------------------------------------------------------
inline Color3& Color3::operator= (const Color3& rkVector) {
    r = rkVector.r;
    g = rkVector.g;
    b = rkVector.b;
    return *this;
}

//----------------------------------------------------------------------------
inline bool Color3::operator== (const Color3& rkVector) const {
    return ( r == rkVector.r && g == rkVector.g && b == rkVector.b );
}

//----------------------------------------------------------------------------
inline bool Color3::operator!= (const Color3& rkVector) const {
    return ( r != rkVector.r || g != rkVector.g || b != rkVector.b );
}

//----------------------------------------------------------------------------
inline Color3 Color3::operator+ (const Color3& rkVector) const {
    return Color3(r + rkVector.r, g + rkVector.g, b + rkVector.b);
}

//----------------------------------------------------------------------------
inline Color3 Color3::operator- (const Color3& rkVector) const {
    return Color3(r -rkVector.r, g - rkVector.g, b - rkVector.b);
}

//----------------------------------------------------------------------------
inline Color3 Color3::operator* (const Color3& rkVector) const {
    return Color3(r * rkVector.r, g  * rkVector.g, b * rkVector.b);
}

//----------------------------------------------------------------------------
inline Color3 Color3::operator- () const {
    return Color3( -r, -g, -b);
}

//----------------------------------------------------------------------------
inline Color3& Color3::operator+= (const Color3& rkVector) {
    r += rkVector.r;
    g += rkVector.g;
    b += rkVector.b;
    return *this;
}

//----------------------------------------------------------------------------
inline Color3& Color3::operator-= (const Color3& rkVector) {
    r -= rkVector.r;
    g -= rkVector.g;
    b -= rkVector.b;
    return *this;
}

//----------------------------------------------------------------------------
inline Color3& Color3::operator*= (float fScalar) {
    r *= fScalar;
    g *= fScalar;
    b *= fScalar;
    return *this;
}

//----------------------------------------------------------------------------
inline Color3& Color3::operator*= (const Color3& rkVector) {
    r *= rkVector.r;
    g *= rkVector.g;
    b *= rkVector.b;
    return *this;
}
//----------------------------------------------------------------------------
inline float Color3::squaredLength () const {
    return r*r + g*g + b*b;
}

//----------------------------------------------------------------------------
inline float Color3::length () const {
    return sqrtf(r*r + g*g + b*b);
}

//----------------------------------------------------------------------------
inline Color3 Color3::direction () const {
    float lenSquared = r * r + g * g + b * b;

    if (lenSquared != 1.0f) {
        return *this / sqrtf(lenSquared);
    } else {
        return *this;
    }
}

//----------------------------------------------------------------------------
inline float Color3::dot (const Color3& rkVector) const {
    return r*rkVector.r + g*rkVector.g + b*rkVector.b;
}

//----------------------------------------------------------------------------
inline Color3 Color3::cross (const Color3& rkVector) const {
    return Color3(g*rkVector.b - b*rkVector.g, b*rkVector.r - r*rkVector.b,
                  r*rkVector.g - g*rkVector.r);
}

//----------------------------------------------------------------------------
inline Color3 Color3::unitCross (const Color3& rkVector) const {
    Color3 kCross(g*rkVector.b - b*rkVector.g, b*rkVector.r - r*rkVector.b,
                  r*rkVector.g - g*rkVector.r);
    return kCross.direction();
}


/** Radiance * measure(Solid Angle) between two points, measured at the receiver orthogonal to the axis between them; W/m^2 */
typedef Color3 Biradiance3;

/** Power per (measure(SolidAngle) * measure(Area));  W / (m^2 sr) */
typedef Color3 Radiance3;

/** Power per area; J / m^2 */
typedef Color3 Radiosity3;

/** Force * distance; J */
typedef Color3 Energy3;

/** Incident power per area;  W/m^2*/
typedef Color3 Irradiance3;

/** Energy per time; W*/
typedef Color3 Power3;

#if 0 // Disabled to avoid taking these useful names from the namespace
typedef float Power;
typedef float Biradiance;
typedef float Radiance;
typedef float Radiosity;
typedef float Energy;
typedef float Irradiance;
#endif
} // namespace


template <> struct HashTrait<G3D::Color3> {
    static size_t hashCode(const G3D::Color3& key) {
        return key.hashCode();
    }
};


#endif
