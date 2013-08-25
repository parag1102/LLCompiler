extern char non_term[10][10] = {"E" , {'\0'}};
extern char term[10][10] = {"a" , "b" , "$" , {'\0'}};
extern char start[10] = "E";
extern char productions_lhs[10][10] = {	"E",
					"E",
					"E",
					"E",
					{'\0'}};

extern char productions_rhs[10][50] = {	"a E b",
					"b E a",
					"a b",
					"b a",
					{'\0'}};
