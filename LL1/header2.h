extern char non_term[10][10] = {"E" , "T" , "F" , {'\0'}};
extern char term[10][10] = {"+" , "*" , "id" , "(" , ")" , "$" , {'\0'}};
extern char start[10] = "E";
extern char productions_lhs[10][10] = {	"E",
					"E",
					"T",
					"T",
					"F",
					"F",
					{'\0'}};

extern char productions_rhs[10][50] = {	"T",
					"E + T",				
					"F",
					"T * F",				
					"id",
					"( E )",
					{'\0'}};
