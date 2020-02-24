#pragma once
#include "oxygine-framework.h"

using namespace oxygine;


class Questwindow : public Sprite
{
public:
	Questwindow();
	~Questwindow();
private:
	Resources res;
};

typedef oxygine::intrusive_ptr<Questwindow>spQuestwindow;