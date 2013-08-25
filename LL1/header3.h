extern char non_term[10][10] = {"E" , {'\0'}};
extern char term[10][10] = {"(" , ")" , "$" , {'\0'}};
extern char start[10] = "E";
extern char productions_lhs[10][10] = {	"E",
					"E",
					{'\0'}};

extern char productions_rhs[10][50] = {	"( E ) E",
					"eps",
					{'\0'}};
