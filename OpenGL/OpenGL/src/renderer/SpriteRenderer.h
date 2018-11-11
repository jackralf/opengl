#pragma once

#include <vector>

struct SpriteInfo;
class SpriteRenderer
{
public:
	static SpriteRenderer* getInstance() {
		static SpriteRenderer* _instance = new SpriteRenderer();
		return _instance;
	}

	SpriteRenderer();
	~SpriteRenderer();


	void add(const SpriteInfo* info) { m_SpriteInfoList.push_back(info); };

	void setup();
	void draw();

private:

	std::vector<const SpriteInfo*> m_SpriteInfoList;
};