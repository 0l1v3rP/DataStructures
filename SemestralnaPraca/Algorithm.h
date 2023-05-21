#pragma once
#include "../DataStructures/libds/heap_monitor.h"
#include<libds/adt/list.h>
#include <vector>
#include <functional>
#include <string>
#include "DataItem.h"
#include "libds/adt/sorts.h"
namespace algorithm
{
	// �abl�nov� funkcia "alg" pre algoritmy, ktor� operuj� na d�tov�ch �trukt�rach. 
	// �abl�nov� parametre s�: 
	// T - typ iter�tora pou�it�ho na prech�dzanie d�tovou �trukt�rou
	// X - typ predik�tu (funkcie alebo funk�n�ho objektu), ktor� sa pou��va na filtrovanie prvkov
	// Y - typ oper�cie (funkcie alebo funk�n�ho objektu), ktor� sa pou��va na prid�vanie prvkov do v�slednej d�tov� �trukt�ry
	// Z - typ porovn�vacej funkcie alebo objektu, ktor� sa pou��va na ur�enie, �i prvok sp��a predik�t
	template<typename T, typename X, typename Y, typename Z>
	struct alg
	{
		// Oper�tor () nadefinuje spr�vanie algoritmu
		// Vstupn� parametre s�: 
		// begin a end - iter�tory definuj�ce rozsah prvkov v p�vodnej d�tovovej �trukt�re
		// predicate - predik�t, ktor� sa pou��va na filtrovanie prvkov
		// operation - oper�cia, ktor� sa pou��va na prid�vanie prvkov do v�slednej d�tovovej �trukt�ry
		// strComp - porovn�vacia funkcia alebo objekt, ktor� sa pou��va na ur�enie, �i prvok sp��a predik�t
		// breakOut - bool hodnota, ktor� ur�uje, �i algoritmus m� skon�i�, ke� sa n�jde prv� prvok nesp��aj�ci predik�t
		ds::adt::ImplicitList<DataItem*> operator()(T begin, T end, X predicate, Y operation, Z  strComp, bool breakOut)
		{
			ds::adt::ImplicitList<DataItem*> newDataStructure;
			while (begin != end)
			{
				if (predicate(strComp(*begin)))
				{
					operation(*begin, newDataStructure);
				}
				else if (breakOut) break;
				++begin;
			}
			return newDataStructure;
		}
	};
}
