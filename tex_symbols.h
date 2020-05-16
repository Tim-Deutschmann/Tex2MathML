#ifndef _tex_symbols_h
#define _tex_symbols_h

#include "tex2mml_data_types.h"

struct TexSymbol_s GlobalTexSymbol[] =
{
//------------------ functions ---------------------
	{"arccos",	true,	true,	false,	"0",	""},
	{"arcsin",	true,	true,	false,	"0",	""},
	{"arctan",	true,	true,	false,	"0",	""},
	{"arg",	true,	true,	false,	"0",	""},
	{"bmod",	true,	false,	false,	"mod",	""},
	{"cos",	true,	true,	false,	"0",	""},
	{"cosh",	true,	true,	false,	"0",	""},
	{"cot",	true,	true,	false,	"0",	""},
	{"coth",	true,	true,	false,	"0",	""},
	{"csc",	true,	true,	false,	"0",	""},
	{"deg",	true,	true,	false,	"0",	""},
	{"det",	true,	true,	false,	"0",	""},
	{"dim",	true,	true,	false,	"0",	""},
	{"exp",	true,	true,	false,	"0",	""},
	{"inf",	true,	true,	false,	"0",	""},
	{"injlim",	true,	false,	false,	"inj lim",	""},
	{"lim",	true,	true,	false,	"0",	""},
	{"liminf",	true,	false,	false,	"lim inf",	""},
	{"limsup",	true,	false,	false,	"lim sup",	""},
	{"gcd",	true,	true,	false,	"0",	""},
	{"hom",	true,	true,	false,	"0",	""},
	{"ker",	true,	true,	false,	"0",	""},
	{"lg",	true,	true,	false,	"0",	""},
	{"ln",	true,	true,	false,	"0",	""},
	{"log",	true,	true,	false,	"0",	""},
	{"Pr",	true,	true,	false,	"0",	""},
	{"sec",	true,	true,	false,	"0",	""},
	{"sin",	true,	true,	false,	"0",	""},
	{"sinh",	true,	true,	false,	"0",	""},
	{"tan",	true,	true,	false,	"0",	""},
	{"tanh",	true,	true,	false,	"0",	""},
	{"max",	true,	true,	false,	"0",	""},
	{"min",	true,	true,	false,	"0",	""},
	{"projlim",	true,	false,	false,	"proj lim",	""},
	{"sup",	true,	true,	false,	"0",	""},
//------------------ greek symbols -----------------	
	{"alpha",	false,	true,	true,	"0",	""},
	{"Alpha",	false,	true,	true,	"0",	""},
	{"beta",	false,	true,	true,	"0",	""},
	{"Beta",	false,	true,	true,	"0",	""},
	{"chi",	false,	true,	true,	"0",	""},
	{"Chi",	false,	true,	true,	"0",	""},
	{"delta",	false,	true,	true,	"0",	""},
	{"Delta",	false,	true,	true,	"0",	""},
	{"digamma",	false,	true,	true,	"0",	""},
	{"Digamma",	false,	true,	true,	"0",	""},
	{"epsilon",	false,	true,	true,	"0",	""},
	{"Epsilon",	false,	true,	true,	"0",	""},
	{"eta",	false,	true,	true,	"0",	""},
	{"Eta",	false,	true,	true,	"0",	""},
	{"gamma",	false,	true,	true,	"0",	""},
	{"Gamma",	false,	true,	true,	"0",	""},
	{"iota",	false,	true,	true,	"0",	""},
	{"Iota",	false,	true,	true,	"0",	""},
	{"kappa",	false,	true,	true,	"0",	""},
	{"Kappa",	false,	true,	true,	"0",	""},
	{"lambda",	false,	true,	true,	"0",	""},
	{"Lambda",	false,	true,	true,	"0",	""},
	{"mu",	false,	true,	true,	"0",	""},
	{"Mu",	false,	true,	true,	"0",	""},
	{"nu",	false,	true,	true,	"0",	""},
	{"Nu",	false,	true,	true,	"0",	""},
	{"omega",	false,	true,	true,	"0",	""},
	{"Omega",	false,	true,	true,	"0",	""},
	{"phi",	false,	true,	true,	"0",	""},
	{"Phi",	false,	true,	true,	"0",	""},
	{"pi",	false,	true,	true,	"0",	""},
	{"Pi",	false,	true,	true,	"0",	""},
	{"psi",	false,	true,	true,	"0",	""},
	{"Psi",	false,	true,	true,	"0",	""},
	{"rho",	false,	true,	true,	"0",	""},
	{"Rho",	false,	true,	true,	"0",	""},
	{"sigma",	false,	true,	true,	"0",	""},
	{"Sigma",	false,	true,	true,	"0",	""},
	{"tau",	false,	true,	true,	"0",	""},
	{"Tau",	false,	true,	true,	"0",	""},
	{"theta",	false,	true,	true,	"0",	""},
	{"Theta",	false,	true,	true,	"0",	""},
	{"upsilon",	false,	true,	true,	"0",	""},
	{"Upsilon",	false,	true,	true,	"0",	""},
	{"varepsilon",	false,	true,	true,	"0",	""},
	{"varkappa",	false,	true,	true,	"0",	""},
	{"varphi",	false,	true,	true,	"0",	""},
	{"varpi",	false,	true,	true,	"0",	""},
	{"varrho",	false,	true,	true,	"0",	""},
	{"varsigma",	false,	true,	true,	"0",	""},
	{"vartheta",	false,	true,	true,	"0",	""},
	{"xi",	false,	true,	true,	"0",	""},
	{"Xi",	false,	true,	true,	"0",	""},
	{"zeta",	false,	true,	true,	"0",	""},
	{"Zeta",	false,	true,	true,	"0",	""},
//------------------ ellipsis (dots) characters ---------
	{"cdots",	true,	false,	true,	"#x2026",	""},
	{"ddots",	true,	false,	true,	"#x22f1",	""},
	{"dots",	true,	false,	true,	"#x2026",	""},
	{"dotsb",	true,	false,	true,	"#x00b7",	""},
	{"dotsc",	true,	false,	true,	"#x2026",	""},
	{"dotsi",	true,	false,	true,	"#x22c5",	""},
	{"dotsm",	true,	false,	true,	"#x22c5",	""},
	{"dotso",	true,	false,	true,	"#x2026",	""},
	{"hdots",	true,	false,	true,	"#x2026",	""},
	{"ldots",	true,	false,	true,	"#x2026",	""},
	{"vdots",	true,	false,	true,	"#x22ee",	""},
//------------------ punctuation and spaces -------------
	{"quad",	true,	false,	true,	"#x2003",	""},
	{"qquad",	true,	false,	true,	"#x2003",	""},
	{"thickspace",	true,	false,	true,	"#x2002",	""},
	{";",	true,	false,	true,	"#x2002",	""},
	{"medspace",	true,	false,	true,	"#x2005",	""},
	{":",	true,	false,	true,	"#x2005",	""},
	{"thinspace",	true,	false,	true,	"#x2004",	""},
	{",",	true,	false,	true,	"#x2004",	""},
	{"!",	true,	false,	true,	"#x200b",	""},
//------------------ delimiters ------------------------
	{"lgroup",	true,	false,	true,	"(",	""},
	{"rgroup",	true,	false,	true,	")",	""},
	{"lbrace",	true,	false,	true,	"{",	""},
	{"rbrace",	true,	false,	true,	"}",	""},
	{"lvert",	true,	false,	true,	"#x007c",	""},
	{"rvert",	true,	false,	true,	"#x007c",	""},
	{"lVert",	true,	false,	true,	"#x2016",	""},
	{"lceil",	true,	false,	true,	"#x2308",	""},
	{"lfloor",	true,	false,	true,	"#x230a",	""},
	{"lmoustache",	true,	false,	true,	"#x23b0",	""},
	{"langle",	true,	false,	true,	"#x2329",	""},
	{"rVert",	true,	false,	true,	"#x2016",	""},
	{"rceil",	true,	false,	true,	"#x2309",	""},
	{"rfloor",	true,	false,	true,	"#x230b",	""},
	{"rmoustache",	true,	false,	true,	"#x23b1",	""},
	{"rangle",	true,	false,	true,	"#x232a",	""},
//------------------ big operators ----------------------
	{"bigcap",	true,	false,	true,	"#x22c2",	""},
	{"bigcup",	true,	false,	true,	"#x22c3",	""},
	{"bigodot",	true,	false,	true,	"#x2a00",	""},
	{"bigoplus",	true,	false,	true,	"#x2a01",	""},
	{"bigotimes",	true,	false,	true,	"#x2a02",	""},
	{"bigsqcup",	true,	false,	true,	"#x2a06",	""},
	{"biguplus",	true,	false,	true,	"#x2a04",	""},
	{"bigvee",	true,	false,	true,	"#x22c1",	""},
	{"bigwedge",	true,	false,	true,	"#x22c0",	""},
	{"coprod",	true,	false,	true,	"#x2210",	""},
	{"prod",	true,	false,	true,	"#x220f",	""},
	{"sum",	true,	false,	true,	"#x2211",	""},
	{"downarrow",	true,	false,	true,	"#x2193",	""},
	{"Downarrow",	true,	false,	true,	"#x21d3",	""},
	{"uparrow",	true,	false,	true,	"#x2191",	""},
	{"Uparrow",	true,	false,	true,	"#x21d1",	""},
	{"updownarrow",	true,	false,	true,	"#x2195",	""},
	{"Updownarrow",	true,	false,	true,	"#x21d5",	""},
//------------------ integrals ---------------------
	{"int",	true,	false,	true,	"#x222b",	""},
	{"oint",	true,	false,	true,	"#x222e",	""},
	{"smallint",	true,	false,	true,	"#x222b",	""},
//------------------ comparison symbols ------------
	{"approx",	true,	false,	true,	"#x2248",	""},
	{"approxeq",	true,	false,	true,	"#x224a",	""},
	{"asymp",	true,	false,	true,	"#x224d",	""},
	{"backsim",	true,	false,	true,	"#x223d",	""},
	{"backsimeq",	true,	false,	true,	"#x22cd",	""},
	{"bumpeq",	true,	false,	true,	"#x224f",	""},
	{"Bumpeq",	true,	false,	true,	"#x224e",	""},
	{"circeq",	true,	false,	true,	"#x2257",	""},
	{"curlyeqprec",	true,	false,	true,	"#x22de",	""},
	{"curlyeqsucc",	true,	false,	true,	"#x22df",	""},
	{"doteq",	true,	false,	true,	"#x2250",	""},
	{"doteqdot",	true,	false,	true,	"#x2251",	""},
	{"eqcirc",	true,	false,	true,	"#x2256",	""},
	{"eqsim",	true,	false,	true,	"#x2242",	""},
	{"eqslantgtr",	true,	false,	true,	"#x2a96",	""},
	{"eqslantless",	true,	false,	true,	"#x2a95",	""},
	{"equiv",	true,	false,	true,	"#x2261",	""},
	{"fallingdotseq",	true,	false,	true,	"#x2252",	""},
	{"gt",	true,	false,	false,	">",	""},
	{"ge",	true,	false,	true,	"#x2265",	""},
	{"geq",	true,	false,	true,	"#x2265",	""},
	{"geqq",	true,	false,	true,	"#x2267",	""},
	{"geqslant",	true,	false,	true,	"#x2a7e",	""},
	{"gg",	true,	false,	true,	"#x226b",	""},
	{"ggg",	true,	false,	true,	"#x22d9",	""},
	{"gggtr",	true,	false,	true,	"#x22d9",	""},
	{"gnapprox",	true,	false,	true,	"#x2a8a",	""},
	{"gneq",	true,	false,	true,	"#x2a88",	""},
	{"gneqq",	true,	false,	true,	"#x2269",	""},
	{"gnsim",	true,	false,	true,	"#x22e7",	""},
	{"gtrapprox",	true,	false,	true,	"#x2a86",	""},
	{"gtreqless",	true,	false,	true,	"#x22db",	""},
	{"gtreqqless",	true,	false,	true,	"#x2a8c",	""},
	{"gtrless",	true,	false,	true,	"#x2277",	""},
	{"gtrsim",	true,	false,	true,	"#x2273",	""},
	{"gvertneqq",	true,	false,	true,	"#x2269",	""},
	{"lt",	true,	false,	false,	"<",	""},
	{"le",	true,	false,	true,	"#x2264",	""},
	{"leq",	true,	false,	true,	"#x2264",	""},
	{"leqq",	true,	false,	true,	"#x2266",	""},
	{"leqslant",	true,	false,	true,	"#x2a7d",	""},
	{"lessapprox",	true,	false,	true,	"#x2a85",	""},
	{"lesseqgtr",	true,	false,	true,	"#x22da",	""},
	{"lesseqqgtr",	true,	false,	true,	"#x2a8b",	""},
	{"lessgtr",	true,	false,	true,	"#x2276",	""},
	{"lesssim",	true,	false,	true,	"#x2272",	""},
	{"ll",	true,	false,	true,	"#x226a",	""},
	{"llless",	true,	false,	true,	"#x22d8",	""},
	{"lnapprox",	true,	false,	true,	"#x2a89",	""},
	{"lneq",	true,	false,	true,	"#x2a87",	""},
	{"lneqq",	true,	false,	true,	"#x2268",	""},
	{"lnsim",	true,	false,	true,	"#x22e6",	""},
	{"lvertneqq",	true,	false,	true,	"#x2268",	""},
	{"ncong",	true,	false,	true,	"#x2247",	""},
	{"ne",	true,	false,	true,	"#x2260",	""},
	{"neq",	true,	false,	true,	"#x2260",	""},
	{"ngeq",	true,	false,	true,	"#x2271",	""},
	{"ngeqq",	true,	false,	true,	"#x2267",	""},
	{"ngeqslant",	true,	false,	true,	"#x2a7e",	""},
	{"ngtr",	true,	false,	true,	"#x226f",	""},
	{"nleq",	true,	false,	true,	"#x2270",	""},
	{"nleqq",	true,	false,	true,	"#x2266",	""},
	{"neqslant",	true,	false,	true,	"#x2a7d",	""},
	{"nless",	true,	false,	true,	"#x226e",	""},
	{"nprec",	true,	false,	true,	"#x2280",	""},
	{"npreceq",	true,	false,	true,	"#x2aaf",	""},
	{"nsim",	true,	false,	true,	"#x2241",	""},
	{"nsucc",	true,	false,	true,	"#x2281",	""},
	{"nsucceq",	true,	false,	true,	"#x2ab0",	""},
	{"prec",	true,	false,	true,	"#x227a",	""},
	{"precapprox",	true,	false,	true,	"#x2ab7",	""},
	{"preccurlyeq",	true,	false,	true,	"#x227c",	""},
	{"preceq",	true,	false,	true,	"#x2aaf",	""},
	{"precnapprox",	true,	false,	true,	"#x2ab9",	""},
	{"precneqq",	true,	false,	true,	"#x2ab5",	""},
	{"precnsim",	true,	false,	true,	"#x22e8",	""},
	{"precsim",	true,	false,	true,	"#x227e",	""},
	{"rsingdotseq",	true,	false,	true,	"#x2253",	""},
	{"sim",	true,	false,	true,	"#x223c",	""},
	{"simeq",	true,	false,	true,	"#x2243",	""},
	{"succ",	true,	false,	true,	"#x227b",	""},
	{"succeq",	true,	false,	true,	"#x2ab0",	""},
	{"succapprox",	true,	false,	true,	"#x2aba",	""},
	{"succneqq",	true,	false,	true,	"#x2ab6",	""},
	{"succnsim",	true,	false,	true,	"#x22e9",	""},
	{"succsim",	true,	false,	true,	"#x227f",	""},
	{"thickapprox",	true,	false,	true,	"#x2248",	""},
	{"thicksim",	true,	false,	true,	"#x223c",	""},
	{"triangleq",	true,	false,	true,	"#x225c",	""},
//------------------ miscellaneous simple symbols ---------------
	{"angle",	true,	false,	true,	"#x2220",	""},
	{"backprime",	true,	false,	true,	"#x2035",	""},
	{"bigstar",	true,	false,	true,	"#x2605",	""},
	{"blacklozenge",	true,	false,	true,	"#x29eb",	""},
	{"blacksquare",	true,	false,	true,	"#x25aa",	""},
	{"blacktriangle",	true,	false,	true,	"#x25b4",	""},
	{"blacktriangledown",	true,	false,	true,	"#x25be",	""},
	{"bot",	true,	false,	true,	"#x22a5",	""},
	{"clubsuit",	true,	false,	true,	"#x2663",	""},
	{"diagdown",	true,	false,	true,	"#x2572",	""},
	{"diagup",	true,	false,	true,	"#x2571",	""},
	{"diamondsuit",	true,	false,	true,	"#x2662",	""},
	{"emptyset",	true,	false,	true,	"#x2205",	""},
	{"exists",	true,	false,	true,	"#x2203",	""},
	{"flat",	true,	false,	true,	"#x266d",	""},
	{"forall",	true,	false,	true,	"#x2200",	""},
	{"heartsuit",	true,	false,	true,	"#x2661",	""},
	{"infty",	true,	false,	true,	"#x221e",	""},
	{"lnot",	true,	false,	true,	"#x00ac",	""},
	{"lozenge",	true,	false,	true,	"#x25ca",	""},
	{"measuredangle",	true,	false,	true,	"#x2221",	""},
	{"nabla",	true,	false,	true,	"#x2207",	""},
	{"natural",	true,	false,	true,	"#x266e",	""},
	{"neg",	true,	false,	true,	"#x00ac",	""},
	{"nexists",	true,	false,	true,	"#x2204",	""},
	{"prime",	true,	false,	true,	"#x2032",	""},
	{"sharp",	true,	false,	true,	"#x266f",	""},
	{"surd",	true,	false,	true,	"#x221a",	""},
	{"top",	true,	false,	true,	"#x22a4",	""},
	{"triangle",	true,	false,	true,	"#x25b5",	""},
	{"triangledown",	true,	false,	true,	"#x25bf",	""},
	{"varnothing",	true,	false,	true,	"#x2205",	""},
//------------------ miscellaneous ---------------------------------
	{"backepsilon",	true,	false,	true,	"#x03f6",	""},
	{"because",	true,	false,	true,	"#x2235",	""},
	{"between",	true,	false,	true,	"#x226c",	""},
	{"blacktriangleleft",	true,	false,	true,	"#x25c0",	""},
	{"blacktriangleright",	true,	false,	true,	"#x25b6",	""},
	{"bowtie",	true,	false,	true,	"#x22c8",	""},
	{"dashv",	true,	false,	true,	"#x22a3",	""},
	{"frown",	true,	false,	true,	"#x2323",	""},
	{"in",	true,	false,	true,	"#x220a",	""},
	{"mid",	true,	false,	true,	"#x2223",	""},
	{"models",	true,	false,	true,	"#x22a7",	""},
	{"ni",	true,	false,	true,	"#x220b",	""},
	{"nmid",	true,	false,	true,	"#x2224",	""},
	{"nshortparallel",	true,	false,	true,	"#x2226",	""},
	{"nsubseteq",	true,	false,	true,	"#x2288",	""},
	{"nsubseteqq",	true,	false,	true,	"#x2ac5",	""},
	{"nsupseteq",	true,	false,	true,	"#x2289",	""},
	{"nsupseteqq",	true,	false,	true,	"#x2ac6",	""},
	{"ntriangleleft",	true,	false,	true,	"#x22ea",	""},
	{"ntrianglelefteq",	true,	false,	true,	"#x22ec",	""},
	{"ntriangleright",	true,	false,	true,	"#x22eb",	""},
	{"ntrianglerighteq",	true,	false,	true,	"#x22ed",	""},
	{"nvdash",	true,	false,	true,	"#x22ac",	""},
	{"nvDash",	true,	false,	true,	"#x22ad",	""},
	{"nVdash",	true,	false,	true,	"#x22ae",	""},
	{"nVDash",	true,	false,	true,	"#x22af",	""},
	{"owns",	true,	false,	true,	"#x220d",	""},
	{"parallel",	true,	false,	true,	"#x2225",	""},
	{"perp",	true,	false,	true,	"#x22a5",	""},
	{"pitchfork",	true,	false,	true,	"#x22d4",	""},
	{"propto",	true,	false,	true,	"#x221d",	""},
	{"shortmid",	true,	false,	true,	"#x2223",	""},
	{"shortparallel",	true,	false,	true,	"#x2225",	""},
	{"smallfrown",	true,	false,	true,	"#x2322",	""},
	{"smallsmile",	true,	false,	true,	"#x2323",	""},
	{"smile",	true,	false,	true,	"#x2223",	""},
	{"sqsubset",	true,	false,	true,	"#x228f",	""},
	{"sqsubseteq",	true,	false,	true,	"#x2291",	""},
	{"subset",	true,	false,	true,	"#x2282",	""},
	{"Subset",	true,	false,	true,	"#x22d0",	""},
	{"subseteq",	true,	false,	true,	"#x2286",	""},
	{"subseteqq",	true,	false,	true,	"#x2ac5",	""},
	{"subsetneq",	true,	false,	true,	"#x228a",	""},
	{"subsetneqq",	true,	false,	true,	"#x2acb",	""},
	{"supset",	true,	false,	true,	"#x2283",	""},
	{"Supset",	true,	false,	true,	"#x22d1",	""},
	{"supseteq",	true,	false,	true,	"#x2287",	""},
	{"supseteqq",	true,	false,	true,	"#x2ac6",	""},
	{"supsetneq",	true,	false,	true,	"#x228b",	""},
	{"supsetneqq",	true,	false,	true,	"#x2acc",	""},
	{"therefore",	true,	false,	true,	"#x2234",	""},
	{"trianglelefteq",	true,	false,	true,	"#x22b4",	""},
	{"trianglerighteq",	true,	false,	true,	"#x22b5",	""},
	{"varpropto",	true,	false,	true,	"#x221d",	""},
	{"varsubsetneq",	true,	false,	true,	"#x228a",	""},
	{"varsubsetneqq",	true,	false,	true,	"#x2acb",	""},
	{"varsupsetneq",	true,	false,	true,	"#x228b",	""},
	{"varsupsetneqq",	true,	false,	true,	"#x2acc",	""},
	{"vartriangle",	true,	false,	true,	"#x25b5",	""},
	{"vartriangleleft",	true,	false,	true,	"#x22b2",	""},
	{"vartriangleright",	true,	false,	true,	"#x22b3",	""},
	{"vdash",	true,	false,	true,	"#x22a2",	""},
	{"vDash",	true,	false,	true,	"#x22a8",	""},
	{"Vdash",	true,	false,	true,	"#x22a9",	""},
	{"Vvdash",	true,	false,	true,	"#x22aa",	""},
//------------------ other alphabetic symbols -----------
	{"aleph",	true,	false,	true,	"#x2135",	""},
	{"Bbbk",	true,	false,	true,	"#x1d55",	""},
	{"beth",	true,	false,	true,	"#x2136",	""},
	{"circledS",	true,	false,	true,	"#x24c8",	""},
	{"complement",	true,	false,	true,	"#x2201",	""},
	{"daleth",	true,	false,	true,	"#x2138",	""},
	{"ell",	true,	false,	true,	"#x2113",	""},
	{"eth",	true,	false,	true,	"#x00f0",	""},
	{"Finv",	true,	false,	true,	"#x2132",	""},
	{"Game",	true,	false,	true,	"#x2141",	""},
	{"gimel",	true,	false,	true,	"#x2137",	""},
	{"hbar",	true,	false,	true,	"#x210f",	""},
	{"hslash",	true,	false,	true,	"#x210f",	""},
	{"lm",	true,	false,	true,	"#x2111",	""},
	{"mho",	true,	false,	true,	"#x2127",	""},
	{"partial",	true,	false,	true,	"#x2202",	"lspace = 0 rspace = 0"},
	{"diff",	true,	false,	false,	"d",	"lspace = 0 rspace = 0"},
	{"Re",	true,	false,	true,	"#x211c",	""},
	{"wp",	true,	false,	true,	"#x2118",	""},
//------------------ arrows -----------------------------
	{"curvearrowleft",	true,	false,	true,	"#x21b6",	""},
	{"curvearrowright",	true,	false,	true,	"#x21b7",	""},
	{"downdownarrows",	true,	false,	true,	"#x21ca",	""},
	{"downharpoonleft",	true,	false,	true,	"#x21c3",	""},
	{"downharpoonright",	true,	false,	true,	"#x21c2",	""},
	{"gets",	true,	false,	true,	"#x2190",	""},
	{"hookleftarrow",	true,	false,	true,	"#x21a9",	""},
	{"hookrightarrow",	true,	false,	true,	"#x21aa",	""},
	{"leftarrow",	true,	false,	true,	"#x2190",	""},
	{"Leftarrow",	true,	false,	true,	"#x21d0",	""},
	{"leftarrowtail",	true,	false,	true,	"#x21a2",	""},
	{"leftharpoondown",	true,	false,	true,	"#x21bd",	""},
	{"leftharpoonup",	true,	false,	true,	"#x21bc",	""},
	{"leftleftarrows",	true,	false,	true,	"#x21c7",	""},
	{"leftrightarrow",	true,	false,	true,	"#x21bc",	""},
	{"leftrightarrows",	true,	false,	true,	"#x21c6",	""},
	{"leftrightharpoons",	true,	false,	true,	"#x21cb",	""},
	{"leftrightsuigarrow",	true,	false,	true,	"#x21ad",	""},
	{"Lleftarrow",	true,	false,	true,	"#x21da",	""},
	{"longleftarrow",	true,	false,	true,	"#x27f5",	""},
	{"Longleftarrow",	true,	false,	true,	"#x27f8",	""},
	{"logleftrightarrow",	true,	false,	true,	"#x27f7",	""},
	{"Longleftrightarrow",	true,	false,	true,	"#x27fa",	""},
	{"looparrowleft",	true,	false,	true,	"#x21ab",	""},
	{"looparrowright",	true,	false,	true,	"#x21ac",	""},
	{"Lsh",	true,	false,	true,	"#x21b0",	""},
	{"mapsto",	true,	false,	true,	"#x21a6",	""},
	{"multimap",	true,	false,	true,	"#x22b8",	""},
	{"nearrow",	true,	false,	true,	"#x2197",	""},
	{"nleftarrow",	true,	false,	true,	"#x219a",	""},
	{"nLeftarrow",	true,	false,	true,	"#x21cd",	""},
	{"nleftrightarrow",	true,	false,	true,	"#x21ae",	""},
	{"nLeftrightarrow",	true,	false,	true,	"#x21ce",	""},
	{"nrightarrow",	true,	false,	true,	"#x219b",	""},
	{"nRightarrow",	true,	false,	true,	"#x21cf",	""},
	{"nwarrow",	true,	false,	true,	"#x2196",	""},
	{"restriction",	true,	false,	true,	"#x21be",	""},
	{"rightarrow",	true,	false,	true,	"#x2192",	""},
	{"Rightarrow",	true,	false,	true,	"#x21d2",	""},
	{"rightarrowtail",	true,	false,	true,	"#x21a3",	""},
	{"rightharpoondown",	true,	false,	true,	"#x21c1",	""},
	{"rightharpoonup",	true,	false,	true,	"#x21c0",	""},
	{"rightleftarrows",	true,	false,	true,	"#x21c4",	""},
	{"rightleftharpoons",	true,	false,	true,	"#x21cc",	""},
	{"rightrightarrows",	true,	false,	true,	"#x21c9",	""},
	{"rightsquidarrow",	true,	false,	true,	"#x219d",	""},
	{"Rrightarrow",	true,	false,	true,	"#x21db",	""},
	{"Rsh",	true,	false,	true,	"#x21b1",	""},
	{"searrow",	true,	false,	true,	"#x2198",	""},
	{"swarrow",	true,	false,	true,	"#x2199",	""},
	{"to",	true,	false,	true,	"#x2192",	""},
	{"twoheadleftarrow",	true,	false,	true,	"#x219e",	""},
	{"twoheadrightarrow",	true,	false,	true,	"#x21a0",	""},
	{"upharpoonleft",	true,	false,	true,	"#x21bf",	""},
	{"upharpoonright",	true,	false,	true,	"#x21be",	""},
	{"upuparrows",	true,	false,	true,	"#x21c8",	""},
//------------------ operator symbols -------------------
	{"amalg",	true,	false,	true,	"#x2a3f",	""},
	{"ast",	true,	false,	true,	"#x2217",	""},
	{"barwedge",	true,	false,	true,	"#x22bc",	""},
	{"bigcirc",	true,	false,	true,	"#x25cb",	""},
	{"bigtriangledown",	true,	false,	true,	"#x25bd",	""},
	{"bigtriangleup",	true,	false,	true,	"#x25b3",	""},
	{"boxdot",	true,	false,	true,	"#x22a1",	""},
	{"boxminus",	true,	false,	true,	"#x229f",	""},
	{"boxplus",	true,	false,	true,	"#x229e",	""},
	{"boxtimes",	true,	false,	true,	"#x22a0",	""},
	{"bullet",	true,	false,	true,	"#x2022",	""},
	{"cap",	true,	false,	true,	"#x2229",	""},
	{"Cap",	true,	false,	true,	"#x22d2",	""},
	{"cdot",	true,	false,	true,	"#x22c5",	""},
	{"centerdot",	true,	false,	true,	"#x00b7",	""},
	{"circ",	true,	false,	true,	"#x2218",	""},
	{"circledast",	true,	false,	true,	"#x229b",	""},
	{"circledcirc",	true,	false,	true,	"#x229a",	""},
	{"circleddash",	true,	false,	true,	"#x229d",	""},
	{"cup",	true,	false,	true,	"#x222a",	""},
	{"Cup",	true,	false,	true,	"#x22d3",	""},
	{"curlyvee",	true,	false,	true,	"#x22ce",	""},
	{"curlyedge",	true,	false,	true,	"#x22cf",	""},
	{"dagger",	true,	false,	true,	"#x2020",	""},
	{"ddagger",	true,	false,	true,	"#x2021",	""},
	{"diamond",	true,	false,	true,	"#x22c4",	""},
	{"div",	true,	false,	true,	"#x00f7",	""},
	{"divideontimes",	true,	false,	true,	"#x22c7",	""},
	{"dotplus",	true,	false,	true,	"#x2214",	""},
	{"doublebarwedge",	true,	false,	true,	"#x2306",	""},
	{"doublecap",	true,	false,	true,	"#x22d2",	""},
	{"doublecup",	true,	false,	true,	"#x22d3",	""},
	{"gtrdot",	true,	false,	true,	"#x22d7",	""},
	{"intercal",	true,	false,	true,	"#x22ba",	""},
	{"land",	true,	false,	true,	"#x2227",	""},
	{"leftthreetimes",	true,	false,	true,	"#x22cb",	""},
	{"lessdot",	true,	false,	true,	"#x22d6",	""},
	{"lor",	true,	false,	true,	"#x2228",	""},
	{"ltimes",	true,	false,	true,	"#x22c9",	""},
	{"mp",	true,	false,	true,	"#x2213",	""},
	{"odot",	true,	false,	true,	"#x2299",	""},
	{"ominus",	true,	false,	true,	"#x2296",	""},
	{"oplus",	true,	false,	true,	"#x2295",	""},
	{"oslash",	true,	false,	true,	"#x2298",	""},
	{"otimes",	true,	false,	true,	"#x2297",	""},
	{"pm",	true,	false,	true,	"#x00b1",	""},
	{"rightthreetimes",	true,	false,	true,	"#x22cc",	""},
	{"rtimes",	true,	false,	true,	"#x22ca",	""},
	{"setminus",	true,	false,	true,	"#x2216",	""},
	{"smallsetminus",	true,	false,	true,	"#x2216",	""},
	{"sqcap",	true,	false,	true,	"#x2293",	""},
	{"sqcup",	true,	false,	true,	"#x2294",	""},
	{"star",	true,	false,	true,	"#x22c6",	""},
	{"times",	true,	false,	true,	"#x00d7",	""},
	{"triangleleft",	true,	false,	true,	"#x25c1",	""},
	{"triangleright",	true,	false,	true,	"#x25b7",	""},
	{"uplus",	true,	false,	true,	"#x228e",	""},
	{"vee",	true,	false,	true,	"#x2228",	""},
	{"veebar",	true,	false,	true,	"#x22bb",	""},
	{"wedge",	true,	false,	true,	"#x2227",	""},
	{"wr",	true,	false,	true,	"#x2240",	""},
//------------------ rest ------------------------------
	{"colon",	true,	false,	false,	":",	""},
	{"|",	true,	false,	true,	"#x2016",	""},
	{"#",	true,	true,	false,	"#",	""},
	{"left",	false,	false,	false,	"",	""},
	{"right",	false,	false,	false,	"",	""},
};

#endif // _tex_symbols_h

