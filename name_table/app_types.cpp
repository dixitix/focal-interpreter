//------------------------------------------------------------------------------
// app_types.cpp - реализация методов классов, задающих назначение
// программных объектов.
//------------------------------------------------------------------------------

#include "app_types.h"

void AppVariable::Out(FILE *of)
{
	fprintf(of, "variable. It has ");
	if (_type == USUAL_TYPE) {
		fprintf(of, "usual type. ");
	} else {
		fprintf(of, "indexed type. ");
    }
	fprintf(of, "Address = %d. ", _addr);
}
