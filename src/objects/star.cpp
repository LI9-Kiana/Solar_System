// @author G. Hemingway, copyright 2025 - All rights reserved
/**
 * An entry point for visitors
 * @param visitor - visitor to be accepted
 */
#include "objects/star.h"
#include "visitors/print.h"

void Star::accept(Visitor& visitor)
{
    visitor.visit(*this);
}

/**
 * Returns a dynamically allocated deep copy of this object
 * @return deep copy of the object
 */
[[nodiscard]] Star* Star::clone() const
{
    Star* temp = new Star(name,mass);
    return temp;
}



/**
 * Initializes a star with the provided properties - really only called by
 * the ObjectFactory
 * @param name - name of the object
 * @param mass - mass of the object
 */
Star::Star(const std::string& name, double mass): Object::Object(name,mass,Vector2(), Vector2())
{

}