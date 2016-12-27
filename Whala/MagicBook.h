#pragma once

#include "Item.h"

class MagicBook : public Item
{
public:
	MagicBook();
	~MagicBook();

	void init(glm::vec2 position);

	bool update(Player* player);

private:

};

