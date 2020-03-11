#include "QuestWindow.h"
#include "oxygine-framework.h"


Questwindow::Questwindow()
{
	res.loadXML("res.xml");
	spSprite questWindow = new Sprite();

	//Основное окно к которому прикрепляются все остальные объекты. В данном случае оно занимает 60% по х и 85% по y от размера сцены.
	questWindow->setResAnim(res.getResAnim("OxyMain"));
	questWindow->setSize(getStage()->getSize().x / 100 * 60, getStage()->getSize().y / 100 * 85);
	questWindow->setAnchor(0.5, 0.5);

	//Здесь это окно помещается в центр сцены.
	Vector2 pos = getStage()->getSize() / 2;
	questWindow->setPosition(pos);
	addChild(questWindow);


	//Создание рамки (border) окна
	int massive_x = getStage()->getSize().x / 100 * 70;
	int massive_y = getStage()->getSize().y / 100 * 70;
	pos = { 0,0 };
	bool x = true;
	int j = 0;
	spSprite *borders_sprite = new spSprite[massive_x * 2 + massive_y * 2 + 1];

	float size_x = getStage()->getSize().x / (getStage()->getSize().x / 100 * 70 / 2);

	//Пока правда спавнить прямые линии по горизонтали и вертикали. Ложь наступает когда больше не остаётся места под прямые линии. Сначала спавнятся линии по горизонтали с отметки 0,0. Как только доходит до конца окна, новые рамки начинают появляться по горизонтали с отмеки 0,окно.y-линия.y. Потом тоже самое по вертикали.
	while (true) {
		borders_sprite[j] = new Sprite();
		if (x) {
			if (pos.y == 0 && pos.x >= questWindow->getSize().x) { pos = { 0,questWindow->getSize().y - borders_sprite[0]->getSize().y }; }
			else if (pos.x >= questWindow->getSize().x && pos.y == questWindow->getSize().y - borders_sprite[0]->getSize().y) { pos = { 0,0 }; x = false; }
			else {
				borders_sprite[j]->setResAnim(res.getResAnim("border_main_top_down"));
				borders_sprite[j]->attachTo(questWindow);
				borders_sprite[j]->setSize(size_x, size_x);
				borders_sprite[j]->setPosition(pos);
			}
			pos = { borders_sprite[j]->getPosition().x + borders_sprite[j]->getSize().x , pos.y };
		}
		else {
			if (pos.y >= questWindow->getSize().y - borders_sprite[0]->getSize().y && pos.x == 0) {
				pos = { questWindow->getSize().x - borders_sprite[0]->getSize().x, 0 };
			}
			else if (pos.y >= questWindow->getSize().y - borders_sprite[0]->getSize().y) { break; }
			else {
				borders_sprite[j]->setResAnim(res.getResAnim("border_main_left_right"));
				borders_sprite[j]->attachTo(questWindow);
				borders_sprite[j]->setSize(size_x, size_x);
				borders_sprite[j]->setPosition(pos);
				pos = { pos.x , borders_sprite[j]->getPosition().y + borders_sprite[j]->getSize().y };
			}
		}
		j += 1;
	}

	for (int j = 0; j <= massive_x * 2 + massive_y * 2; j++) {
		if (x) {
			if (j == massive_x) { pos = { 0,questWindow->getSize().y }; }
			else if (pos.x >= questWindow->getSize().x && pos.y == questWindow->getSize().y) { pos = { 0,0 }; x = false; }

			else {
				borders_sprite[j]->setResAnim(res.getResAnim("border_main_top_down"));
				borders_sprite[j]->attachTo(questWindow);
				borders_sprite[j]->setPosition(pos);
			}
		}
	}

	//На это всё лепится по углам плашки-углы
	spSprite border_top_left = new Sprite();
	border_top_left->setResAnim(res.getResAnim("border_top_left"));
	border_top_left->attachTo(questWindow);
	border_top_left->setSize(size_x, size_x);
	border_top_left->setPosition(0, 0);

	spSprite border__top_right = new Sprite();
	border__top_right->setResAnim(res.getResAnim("border_top_right"));
	border__top_right->attachTo(questWindow);
	border__top_right->setSize(size_x, size_x);
	border__top_right->setPosition(questWindow->getSize().x - border__top_right->getSize().x, 0);

	spSprite border_bot_left = new Sprite();
	border_bot_left->setResAnim(res.getResAnim("border_down_left"));
	border_bot_left->attachTo(questWindow);
	border_bot_left->setSize(size_x, size_x);
	border_bot_left->setPosition(0, questWindow->getSize().y - border_bot_left->getSize().y);

	spSprite border_bot_right = new Sprite();
	border_bot_right->setResAnim(res.getResAnim("border_down_right"));
	border_bot_right->attachTo(questWindow);
	border_bot_right->setSize(size_x, size_x);
	border_bot_right->setPosition(questWindow->getSize().x - border_bot_right->getSize().x, questWindow->getSize().y - border_bot_right->getSize().y);

	//Окно со списком всех квестов
	spSprite quest_list_window = new Sprite();
	quest_list_window->setResAnim(res.getResAnim("OxyQuests"));
	quest_list_window->attachTo(questWindow);
	quest_list_window->setSize(questWindow->getSize().x / 100 * 30, questWindow->getSize().y - borders_sprite[0]->getSize().y * 2);
	quest_list_window->setPosition(0 + borders_sprite[0]->getSize().x, 0 + borders_sprite[0]->getSize().y);

	//Кнопки сортировки квестов. Расстояние между кнопками и внутри окна со списоком всех квестов высчитывается автоматически, так что можно в список sort_buttons_text добавлять сколько угодно новых элементов.
	std::string sort_buttons[] = { "Active","Complete" };
	int array_size = sizeof(sort_buttons)/ sizeof(*sort_buttons);
	spButton *sort_buttons_buttons = new spButton[array_size];
	spTextField *sort_buttons_text = new spTextField[array_size];
	float button_size_x = quest_list_window->getSize().x/(array_size+1);
	TextStyle style = TextStyle().alignMiddle();
	pos = { button_size_x / (array_size+1),20 };

	for (int j = 0; j < array_size; j++) {
		sort_buttons_buttons[j] = new Button();
		sort_buttons_buttons[j]->setResAnim(res.getResAnim("SortButtons"));
		sort_buttons_buttons[j]->attachTo(quest_list_window);
		sort_buttons_buttons[j]->setSize(button_size_x, 20);
		sort_buttons_buttons[j]->setPosition(pos);
		//sort_buttons_buttons[j]->setAnchor(0.5, 0.5);

		sort_buttons_text[j] = new TextField();
		sort_buttons_text[j]->setStyle(style);
		sort_buttons_text[j]->setText(sort_buttons[j]);
		sort_buttons_buttons[j]->addChild(sort_buttons_text[j]);
		sort_buttons_text[j]->setPosition(sort_buttons_buttons[j]->getSize() / 2);

		pos = { pos.x + button_size_x + button_size_x / (array_size+1) ,pos.y };
	}

	//Список всех квестов
	std::string quest_list[] = {"Catch the prisoner","Kill the wolves","All you want"};
	pos = { 0,20 * 2 + sort_buttons_buttons[0]->getSize().y };
	spTextField *quest_list_text = new spTextField[sizeof(quest_list) / sizeof(*quest_list)];
	spButton *quest_list_button = new spButton[sizeof(quest_list) / sizeof(*quest_list)];
	for (int j = 0; j < sizeof(quest_list) / sizeof(*quest_list); j++) {
		quest_list_button[j] = new Button();

		quest_list_button[j]->setResAnim(res.getResAnim("OxyQuests"));
		quest_list_button[j]->attachTo(quest_list_window);
		quest_list_button[j]->setSize(quest_list_window->getSize().x,25);
		quest_list_button[j]->setPosition(0,pos.y);

		quest_list_text[j] = new TextField();
		quest_list_text[j]->setText(quest_list[j]);
		quest_list_button[j]->addChild(quest_list_text[j]);

		pos = {pos.x,pos.y+quest_list_button[j]->getSize().y};

	}

	//Расположение Скролла
	spSprite scroll = new Sprite();
	scroll->setResAnim(res.getResAnim("OxyDeclineButton"));
	scroll->attachTo(quest_list_window);
	scroll->setSize(5, 90);
	scroll->setPosition(quest_list_window->getSize().x-scroll->getSize().x, 20 * 2 + sort_buttons_buttons[0]->getSize().y);



}

Questwindow::~Questwindow()
{
	res.free();

}
