#ifndef  SystemTypes_h_
#define SystemTypes_h_

#include <string>
#include <list>
#include <vector>
#include <set>


typedef std::string     tString;
typedef std::list<tString> tStringList;
typedef tStringList::iterator tStringListIt;

typedef std::vector<tString> tStringVec;
typedef tStringVec::iterator tStringVecIt;

typedef std::set<tString> tStringSet;
typedef tStringSet::iterator tStringSetIt;



typedef std::wstring    tWString;

typedef std::list<tWString> tWStringList;
typedef tWStringList::iterator tWStringListIt;

typedef std::vector<tWString> tWStringVec;
typedef tWStringVec::iterator tWStringVecIt;

typedef std::set<tWString> tWStringSet;
typedef tWStringSet::iterator tWStringSetIt;

typedef std::vector<unsigned int> tUIntVec;
typedef tUIntVec::iterator tUIntVecIt;

typedef std::vector<int> tIntVec;
typedef tIntVec::iterator tIntVecIt;

typedef std::vector<float> tFloatVec;
typedef tFloatVec::iterator tFloatVecIt;


typedef unsigned int	Uint32;


#endif // ! SystemTypes_h_



