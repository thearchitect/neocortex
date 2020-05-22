#include "utils.h"

namespace core
{
	/// solve quadratic equation
	bool    SolveQuadratic( const REAL& a, const REAL& b, const REAL&c, REAL& x1, REAL& x2 )
	{
		REAL d = b*b - 4*a*c;
		if ( d < 0 )
			return false;
		else
		{
			REAL den = 1/(2*a);
			x1 = (-b - sqrt(d))*den;
			x2 = (-b + sqrt(d))*den;
			return true;
		}
	}
}