#include "ObjectMatch.h"

ObjectMatch * ObjectMatch::instance = nullptr;



ObjectMatch * ObjectMatch::getInstance()
{
	if(instance) return instance;
	else {
		instance = new ObjectMatch();
		return instance;
	}
}

void ObjectMatch::addMatch(void * ptr1,void * ptr2)
{
	m_objMap.insert(std::make_pair(ptr1,ptr2));
}

void * ObjectMatch::finSecond(void * ptr1)
{
	auto result = m_objMap.find(ptr1);
	if(result == m_objMap.end())
	{
		return NULL;
	}else
	{
		return result->second;
	}
}

ObjectMatch::ObjectMatch()
{

}
