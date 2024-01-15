#include <bits/stdc++.h>
#include <nlohmann/json.hpp>
#include <thread>
#include <mutex>
#include "Game.h"
#include "../Classes/Country.h"
#include "../Classes/Settings.h"

void game(Country& PlayerCountry, Country& EnemyCountry) {
	extern Settings globalSettings;

	std::mutex mtx;
	
	int id = 4;
	int game_month = 1;
	int game_year = 2137;

	std::cout << "GameLogicFunction\n";

	while (1) {
		if (game_month > 12) {
			game_month = 1;
		}


		PlayerCountry.setFoodStockpile(PlayerCountry.getFoodStockpile() + PlayerCountry.getFoodIncome());
		PlayerCountry.setMetalStockpile(PlayerCountry.getMetalStockpile() + PlayerCountry.getMetalIncome());
		PlayerCountry.setUraniumStockpile(PlayerCountry.getUraniumStockpile() + PlayerCountry.getUraniumIncome());

		EnemyCountry.setFoodStockpile(EnemyCountry.getFoodStockpile() + EnemyCountry.getFoodIncome());
		EnemyCountry.setMetalStockpile(EnemyCountry.getMetalStockpile() + EnemyCountry.getMetalIncome());
		EnemyCountry.setUraniumStockpile(EnemyCountry.getUraniumStockpile() + EnemyCountry.getUraniumIncome());


		if (EnemyCountry.getUraniumStockpile() >= 100) {
			EnemyCountry.setUraniumStockpile(EnemyCountry.getUraniumStockpile() - 100);
			EnemyCountry.setNukes(EnemyCountry.getNukes() + 1);
		}
		if (EnemyCountry.getNukes() > 0) {
			EnemyCountry.setNukes(EnemyCountry.getNukes() - 1);
			PlayerCountry.cities[id].setIsDestroyed(true);
			id = id - 1;
		}

		mtx.lock();
		//mvwprintw(clockWin, 1, 3, "Month/Year: %d/%d BFK", game_month, game_year);
		//wrefresh(clockWin);
		mtx.unlock();

		game_month++;
		//napms(500*globalSettings.getSpeed());
	}
}