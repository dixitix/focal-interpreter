#include "name_table.h"

void Out(NameTable &table, FILE *os = stdout) {
	NameTable::iterator i;
	fprintf(os, "Table of names\n");
	for(i = table.begin(); i != table.end(); i++)
	{
		fprintf(os, "%s: ", (*i).first.c_str());

		(*i).second->Out(os);

		fprintf(os, "\n");
	}
	fprintf(os, "Size of Table = %d\n", static_cast<int>(table.size()));
}

void Clear(NameTable &table)
{
	NameTable::iterator i;
	for(i = table.begin(); i != table.end(); i++)
	{
		delete (*i).second;
	}
}
