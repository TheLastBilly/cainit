#include "cainit.hpp"

//HeaderElement
HeaderElement::HeaderElement()
{}

HeaderElement::HeaderElement( std::string header ):
header(header)
{}

HeaderElement::~HeaderElement()
{}

//VariableElement
VariableElement::VariableElement()
{}

VariableElement::VariableElement( std::string type, std::string name ):
type(type), name(name)
{}

VariableElement::~VariableElement()
{}

//ClassUnit
ClassUnit::ClassUnit()
{}

ClassUnit::ClassUnit( std::string name, std::vector<VariableElement> elements ):
name(name), elements(elements)
{}

ClassUnit::~ClassUnit()
{}
