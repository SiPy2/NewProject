#include "Window.h"
#include "oxygine-framework.h"
#include "QuestWindow.h"

void Window_preinit()
{


}

void Window_init()
{
	spQuestwindow questwindow = new Questwindow;
	getStage()->addChild(questwindow);
	//getStage()->setSize(1280, 720);
	//questwindow->setSize(getStage()->getSize().x -100, getStage()->getSize().y -100);
	//core::reset();


}

void Window_destroy()
{



}

void Window_update()
{


}

void Window_flush()
{



}