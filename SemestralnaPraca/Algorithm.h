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
	// Šablónová funkcia "alg" pre algoritmy, ktoré operujú na dátovıch štruktúrach. 
	// Šablónové parametre sú: 
	// T - typ iterátora pouitého na prechádzanie dátovou štruktúrou
	// X - typ predikátu (funkcie alebo funkèného objektu), ktorı sa pouíva na filtrovanie prvkov
	// Y - typ operácie (funkcie alebo funkèného objektu), ktorı sa pouíva na pridávanie prvkov do vıslednej dátové štruktúry
	// Z - typ porovnávacej funkcie alebo objektu, ktorı sa pouíva na urèenie, èi prvok spåòa predikát
	template<typename T, typename X, typename Y, typename Z>
	struct alg
	{
		// Operátor () nadefinuje správanie algoritmu
		// Vstupné parametre sú: 
		// begin a end - iterátory definujúce rozsah prvkov v pôvodnej dátovovej štruktúre
		// predicate - predikát, ktorı sa pouíva na filtrovanie prvkov
		// operation - operácia, ktorá sa pouíva na pridávanie prvkov do vıslednej dátovovej štruktúry
		// strComp - porovnávacia funkcia alebo objekt, ktorı sa pouíva na urèenie, èi prvok spåòa predikát
		// breakOut - bool hodnota, ktorá urèuje, èi algoritmus má skonèi, keï sa nájde prvı prvok nespåòajúci predikát
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
