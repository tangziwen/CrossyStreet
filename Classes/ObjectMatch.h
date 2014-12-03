#ifndef OBJECT_MATCH_H
#define OBJECT_MATCH_H
#include <map>
class ObjectMatch
{
public:
	static ObjectMatch * getInstance();
	void addMatch(void * ptr1,void * ptr2);
	void * finSecond(void * ptr1);
private:

	ObjectMatch();
	static ObjectMatch * instance;
	std::map<void * ,void *> m_objMap;
};
#endif