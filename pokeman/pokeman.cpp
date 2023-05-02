#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <fstream>
#include <Windows.h>


typedef unsigned int uint;

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::getline;

enum pokemon_type {
    NORMAL, FIRE, WATER, ELECTRIC, GRASS,
    ICE, FIGHTING, POISON, GROUND, FLYING,
    PSYCHIC, BUG, ROCK, GHOST, DRAGON, DARK,
    STEEL, FAIRY
};

void input_check( int&input_var )
{
    cin >> input_var;
    while (cin.fail() || (input_var != 1 && input_var != 2 && input_var != 3 && input_var != 4)) // проблема 1/2
    {
        //cout << input_var;
        cout << "Ошибка ввода" << endl;
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail());
        cin >> input_var;
    }
}

pokemon_type parse_string_to_pok_type(string temp)
{

    std::vector<string> mas{"NORMAL", "FIRE", "WATER", "ELECTRIC", "GRASS", "ICE", "FIGHTING", "POISON", "GROUND", "FLYING", "PSYCHIC", "BUG", "ROCK", "GHOST", "DRAGON", "DARK", "STEEL", "FAIRY"};

    for (int i = 0; i < mas.size() ; ++i)
    {
        if (temp == mas[i])
            return pokemon_type(i);
    }
    return pokemon_type(0);
}


struct Pokemon
{
    uint ID;
    string NAME;
    pokemon_type TYPE;

    struct
    {
        int HEALTH;
        int DEFENCE;
        pokemon_type WEAKNESS;
        int SPEED;
    }STATS;

    //struct
    //{
    //    struct
    //    {
    //        string ATCK_NAME;
    //        int DAMAGE;
    //    }ATTACK_1;

    //    struct
    //    {
    //        string ATCK_NAME;
    //        int DAMAGE;
    //    }ATTACK_2;

    //    struct
    //    {
    //        string ATCK_NAME;
    //        int DAMAGE;
    //    }ATTACK_3;

    //}ATTACKS;

    struct
    {
        string ATCK_NAME;
        int DAMAGE;
        int ENERGY;
    }ATTACKS[3];

    void fightt(Pokemon pfirst, Pokemon psecond)
    {
        cout << "Бой начался между: " << pfirst.NAME << " и " << psecond.NAME << endl;
        int fta;
        if (pfirst.STATS.SPEED >= psecond.STATS.SPEED)
            fta = 0;
        else
            fta = 1;

        if (fta)
            cout << "Первым атакует " << psecond.NAME << endl;
        else
            cout << "Первым атакует " << pfirst.NAME << endl;

        int round = 1;

        int first_weak, second_weak;

        if (pfirst.STATS.WEAKNESS == psecond.TYPE)
        {
            first_weak = 2;
        }
        else
            first_weak = 1;

        if (pfirst.TYPE == psecond.STATS.WEAKNESS)
        {
            second_weak = 2;
        }
        else
            second_weak = 1;
        
        int first_energy  = 50;
        int second_energy = 50;

        while (true)
        {
            cout << "Раунд: " << round << " Характеристики покемонов: " <<
                pfirst.NAME << " здоровье - " << pfirst.STATS.HEALTH << " Энергия - " << first_energy <<
                "   " << psecond.NAME << " здоровье - " << psecond.STATS.HEALTH << " Энергия - " << second_energy;
            cout << "\n";


            if (fta % 2 == 0)
            {
                int attack_id;
                string fname = pfirst.NAME;
                string sname = psecond.NAME;
                /*cout << "Выберите атаку против " << psecond.NAME;
                cout << endl << "Введите \"1\" для атаки " << pfirst.ATTACKS.ATTACK_1.ATCK_NAME
                    << " она нанесет " << pfirst.ATTACKS.ATTACK_1.DAMAGE;

                cout << endl << "Введите \"2\" для атаки " << pfirst.ATTACKS.ATTACK_2.ATCK_NAME
                    << " она нанесет " << pfirst.ATTACKS.ATTACK_2.DAMAGE;

                cout << endl << "Введите \"3\" для атаки " << pfirst.ATTACKS.ATTACK_3.ATCK_NAME
                    << " она нанесет " << pfirst.ATTACKS.ATTACK_3.DAMAGE;
                cout << endl;*/
                
                cout << "Выберите атаку против " << psecond.NAME;

                if (second_weak == 2)
                    cout << "\nПокемон " << sname << " слаб против аттак " << fname;

                if (pfirst.ATTACKS[0].ENERGY - first_energy <= 0)
                {
                    cout << endl << "Введите \"1\" для атаки " << pfirst.ATTACKS[0].ATCK_NAME
                        << " она нанесет " << (second_weak * pfirst.ATTACKS[0].DAMAGE) - psecond.STATS.DEFENCE << " и затратит " << pfirst.ATTACKS[0].ENERGY;
                }
                else
                    cout << endl << "Вам не хватает энергии для атаки " << pfirst.ATTACKS[0].ATCK_NAME;
                
                if (pfirst.ATTACKS[1].ENERGY - first_energy <= 0)
                {
                    cout << endl << "Введите \"2\" для атаки " << pfirst.ATTACKS[1].ATCK_NAME
                        << " она нанесет " << (second_weak * pfirst.ATTACKS[1].DAMAGE) - psecond.STATS.DEFENCE << " и затратит " << pfirst.ATTACKS[1].ENERGY;
                }
                else
                    cout << endl << "Вам не хватает энергии для атаки " << pfirst.ATTACKS[1].ATCK_NAME;

                if (pfirst.ATTACKS[2].ENERGY - first_energy <= 0)
                {
                    cout << endl << "Введите \"3\" для атаки " << pfirst.ATTACKS[2].ATCK_NAME
                        << " она нанесет " << (second_weak * pfirst.ATTACKS[2].DAMAGE) - psecond.STATS.DEFENCE << " и затратит " << pfirst.ATTACKS[2].ENERGY;
                }
                else
                    cout << endl << "Вам не хватает энергии для атаки " << pfirst.ATTACKS[2].ATCK_NAME;

                
                cout << endl << "Введите \"4\" для того чтобы пропустить ход" << endl;

                input_check(attack_id);
                

                switch (attack_id)
                {
                case 1:
                {
                    //cout << "Вы выбрали атаку: " << pfirst.ATTACKS[0].ATCK_NAME;
                    
                    int attack_damage = (second_weak*pfirst.ATTACKS[0].DAMAGE) - psecond.STATS.DEFENCE;
                    first_energy -= pfirst.ATTACKS[0].ENERGY;
                    if (attack_damage >= 0)
                        psecond.STATS.HEALTH -= attack_damage;
                    break;
                }
                case 2:
                {
                    int attack_damage = (second_weak * pfirst.ATTACKS[1].DAMAGE) - psecond.STATS.DEFENCE;
                    first_energy -= pfirst.ATTACKS[1].ENERGY;
                    if (attack_damage >= 0)
                        psecond.STATS.HEALTH -= attack_damage;
                    break;
                }
                case 3:
                {
                    int attack_damage = (second_weak * pfirst.ATTACKS[2].DAMAGE) - psecond.STATS.DEFENCE;
                    first_energy -= pfirst.ATTACKS[2].ENERGY;
                    if (attack_damage >= 0)
                        psecond.STATS.HEALTH -= attack_damage;
                    break;
                }
                default:
                    break;
                }

                if (pfirst.STATS.HEALTH <= 0)
                {
                    cout << psecond.NAME << " Побеждает";
                    break;
                }
                else if (psecond.STATS.HEALTH <= 0)
                {
                    cout << pfirst.NAME << " Побеждает";
                    break;
                }

                

                fta++;
                first_energy += 5;
                if (first_energy > 50)
                    first_energy = 50;

                cout << "Конец хода. Теперь ходит " << psecond.NAME << endl;
            }

            else
            {
                int attack_id;
                string fname = pfirst.NAME;
                string sname = psecond.NAME;
                
                cout << "Выберите атаку против " << pfirst.NAME;
                if (first_weak == 2)
                    cout << "\nПокемон " << fname << " слаб против аттак " << sname;

                if (psecond.ATTACKS[0].ENERGY - first_energy <= 0)
                {
                    cout << endl << "Введите \"1\" для атаки " << psecond.ATTACKS[0].ATCK_NAME
                        << " она нанесет " << (first_weak * psecond.ATTACKS[0].DAMAGE) - pfirst.STATS.DEFENCE << " и затратит " << psecond.ATTACKS[0].ENERGY;
                }
                else
                    cout << endl << "Вам не хватает энергии для атаки " << psecond.ATTACKS[0].ATCK_NAME;

                if (psecond.ATTACKS[1].ENERGY - first_energy <= 0)
                {
                    cout << endl << "Введите \"2\" для атаки " << psecond.ATTACKS[1].ATCK_NAME
                        << " она нанесет " << (first_weak * psecond.ATTACKS[1].DAMAGE) - pfirst.STATS.DEFENCE << " и затратит " << psecond.ATTACKS[1].ENERGY;
                }
                else
                    cout << endl << "Вам не хватает энергии для атаки " << psecond.ATTACKS[1].ATCK_NAME;
                
                if (psecond.ATTACKS[2].ENERGY - first_energy <= 0)
                {
                    cout << endl << "Введите \"3\" для атаки " << psecond.ATTACKS[2].ATCK_NAME
                        << " она нанесет " << (first_weak * psecond.ATTACKS[2].DAMAGE) - pfirst.STATS.DEFENCE << " и затратит " << psecond.ATTACKS[2].ENERGY;
                }
                else
                    cout << endl << "Вам не хватает энергии для атаки " << psecond.ATTACKS[2].ATCK_NAME;

                
                cout << endl << "Введите \"4\" для того чтобы пропустить ход" << endl;


                

                input_check(attack_id);

                switch (attack_id)
                {
                case 1:
                {
                    /*int attack_damage = psecond.ATTACKS.ATTACK_1.DAMAGE - pfirst.STATS.DEFENCE;
                    if (attack_damage >= 0)
                        pfirst.STATS.HEALTH -= attack_damage;
                    break;*/
                    
                    int attack_damage = (first_weak * psecond.ATTACKS[0].DAMAGE) - pfirst.STATS.DEFENCE;
                    second_energy -= psecond.ATTACKS[0].ENERGY;
                    if (attack_damage >= 0)
                        pfirst.STATS.HEALTH -= attack_damage;
                    break;
                }
                case 2:
                {
                    int attack_damage = (first_weak * psecond.ATTACKS[1].DAMAGE) - pfirst.STATS.DEFENCE;
                    second_energy -= psecond.ATTACKS[1].ENERGY;
                    if (attack_damage >= 0)
                        pfirst.STATS.HEALTH -= attack_damage;
                    break;
                }
                case 3:
                {
                    int attack_damage = (first_weak * psecond.ATTACKS[2].DAMAGE) - pfirst.STATS.DEFENCE;
                    second_energy -= psecond.ATTACKS[2].ENERGY;
                    if (attack_damage >= 0)
                        pfirst.STATS.HEALTH -= attack_damage;
                    break;
                }
                default:
                    break;
                }

                if (pfirst.STATS.HEALTH <= 0)
                {
                    cout << psecond.NAME << " Побеждает";
                    break;
                }
                else if (psecond.STATS.HEALTH <= 0)
                {
                    cout << pfirst.NAME << " Побеждает";
                    break;
                }

                /*if (psecond.STATS.HEALTH <= 0)
                {
                    cout << psecond.NAME << " Побеждает";
                    break;
                }*/

                fta++;
                second_energy += 5;
                if (second_energy > 50)
                    second_energy = 50;

                cout << "Конец хода. Теперь ходит " << pfirst.NAME << endl;
            }
            round++;
        }
    }
};

void fight(Pokemon pfirst, Pokemon psecond)
{
    cout << "Бой начался между: " << pfirst.NAME << " и " << psecond.NAME << endl;
    int fta;
    if (pfirst.STATS.SPEED >= psecond.STATS.SPEED)
        fta = 0;
    else
        fta = 1;

    if (fta)
        cout << "Первым атакует " << psecond.NAME << endl;
    else
        cout << "Первым атакует " << pfirst.NAME << endl;

    int round = 1;

    int first_weak, second_weak;

    if (pfirst.STATS.WEAKNESS == psecond.TYPE)
    {
        first_weak = 2;
    }
    else
        first_weak = 1;

    if (pfirst.TYPE == psecond.STATS.WEAKNESS)
    {
        second_weak = 2;
    }
    else
        second_weak = 1;

    int first_energy = 50;
    int second_energy = 50;

    while (true)
    {
        cout << "Раунд: " << round << " Характеристики покемонов: " <<
            pfirst.NAME << " здоровье - " << pfirst.STATS.HEALTH << " Энергия - " << first_energy <<
            "   " << psecond.NAME << " здоровье - " << psecond.STATS.HEALTH << " Энергия - " << second_energy;
        cout << "\n";


        if (fta % 2 == 0)
        {
            int attack_id;
            string fname = pfirst.NAME;
            string sname = psecond.NAME;
            /*cout << "Выберите атаку против " << psecond.NAME;
            cout << endl << "Введите \"1\" для атаки " << pfirst.ATTACKS.ATTACK_1.ATCK_NAME
                << " она нанесет " << pfirst.ATTACKS.ATTACK_1.DAMAGE;

            cout << endl << "Введите \"2\" для атаки " << pfirst.ATTACKS.ATTACK_2.ATCK_NAME
                << " она нанесет " << pfirst.ATTACKS.ATTACK_2.DAMAGE;

            cout << endl << "Введите \"3\" для атаки " << pfirst.ATTACKS.ATTACK_3.ATCK_NAME
                << " она нанесет " << pfirst.ATTACKS.ATTACK_3.DAMAGE;
            cout << endl;*/

            cout << "Выберите атаку против " << psecond.NAME;

            if (second_weak == 2)
                cout << "\nПокемон " << sname << " слаб против аттак " << fname;

            if (pfirst.ATTACKS[0].ENERGY - first_energy <= 0)
            {
                cout << endl << "Введите \"1\" для атаки " << pfirst.ATTACKS[0].ATCK_NAME
                    << " она нанесет " << (second_weak * pfirst.ATTACKS[0].DAMAGE) - psecond.STATS.DEFENCE << " и затратит " << pfirst.ATTACKS[0].ENERGY;
            }
            else
                cout << endl << "Вам не хватает энергии для атаки " << pfirst.ATTACKS[0].ATCK_NAME;

            if (pfirst.ATTACKS[1].ENERGY - first_energy <= 0)
            {
                cout << endl << "Введите \"2\" для атаки " << pfirst.ATTACKS[1].ATCK_NAME
                    << " она нанесет " << (second_weak * pfirst.ATTACKS[1].DAMAGE) - psecond.STATS.DEFENCE << " и затратит " << pfirst.ATTACKS[1].ENERGY;
            }
            else
                cout << endl << "Вам не хватает энергии для атаки " << pfirst.ATTACKS[1].ATCK_NAME;

            if (pfirst.ATTACKS[2].ENERGY - first_energy <= 0)
            {
                cout << endl << "Введите \"3\" для атаки " << pfirst.ATTACKS[2].ATCK_NAME
                    << " она нанесет " << (second_weak * pfirst.ATTACKS[2].DAMAGE) - psecond.STATS.DEFENCE << " и затратит " << pfirst.ATTACKS[2].ENERGY;
            }
            else
                cout << endl << "Вам не хватает энергии для атаки " << pfirst.ATTACKS[2].ATCK_NAME;


            cout << endl << "Введите \"4\" для того чтобы пропустить ход" << endl;

            input_check(attack_id);


            switch (attack_id)
            {
            case 1:
            {
                //cout << "Вы выбрали атаку: " << pfirst.ATTACKS[0].ATCK_NAME;

                int attack_damage = (second_weak * pfirst.ATTACKS[0].DAMAGE) - psecond.STATS.DEFENCE;
                first_energy -= pfirst.ATTACKS[0].ENERGY;
                if (attack_damage >= 0)
                    psecond.STATS.HEALTH -= attack_damage;
                break;
            }
            case 2:
            {
                int attack_damage = (second_weak * pfirst.ATTACKS[1].DAMAGE) - psecond.STATS.DEFENCE;
                first_energy -= pfirst.ATTACKS[1].ENERGY;
                if (attack_damage >= 0)
                    psecond.STATS.HEALTH -= attack_damage;
                break;
            }
            case 3:
            {
                int attack_damage = (second_weak * pfirst.ATTACKS[2].DAMAGE) - psecond.STATS.DEFENCE;
                first_energy -= pfirst.ATTACKS[2].ENERGY;
                if (attack_damage >= 0)
                    psecond.STATS.HEALTH -= attack_damage;
                break;
            }
            default:
                break;
            }

            if (pfirst.STATS.HEALTH <= 0)
            {
                cout << psecond.NAME << " Побеждает";
                break;
            }
            else if (psecond.STATS.HEALTH <= 0)
            {
                cout << pfirst.NAME << " Побеждает";
                break;
            }



            fta++;
            first_energy += 5;
            if (first_energy > 50)
                first_energy = 50;

            cout << "Конец хода. Теперь ходит " << psecond.NAME << endl;
        }

        else
        {
            int attack_id;
            string fname = pfirst.NAME;
            string sname = psecond.NAME;

            cout << "Выберите атаку против " << pfirst.NAME;
            if (first_weak == 2)
                cout << "\nПокемон " << fname << " слаб против аттак " << sname;

            if (psecond.ATTACKS[0].ENERGY - first_energy <= 0)
            {
                cout << endl << "Введите \"1\" для атаки " << psecond.ATTACKS[0].ATCK_NAME
                    << " она нанесет " << (first_weak * psecond.ATTACKS[0].DAMAGE) - pfirst.STATS.DEFENCE << " и затратит " << psecond.ATTACKS[0].ENERGY;
            }
            else
                cout << endl << "Вам не хватает энергии для атаки " << psecond.ATTACKS[0].ATCK_NAME;

            if (psecond.ATTACKS[1].ENERGY - first_energy <= 0)
            {
                cout << endl << "Введите \"2\" для атаки " << psecond.ATTACKS[1].ATCK_NAME
                    << " она нанесет " << (first_weak * psecond.ATTACKS[1].DAMAGE) - pfirst.STATS.DEFENCE << " и затратит " << psecond.ATTACKS[1].ENERGY;
            }
            else
                cout << endl << "Вам не хватает энергии для атаки " << psecond.ATTACKS[1].ATCK_NAME;

            if (psecond.ATTACKS[2].ENERGY - first_energy <= 0)
            {
                cout << endl << "Введите \"3\" для атаки " << psecond.ATTACKS[2].ATCK_NAME
                    << " она нанесет " << (first_weak * psecond.ATTACKS[2].DAMAGE) - pfirst.STATS.DEFENCE << " и затратит " << psecond.ATTACKS[2].ENERGY;
            }
            else
                cout << endl << "Вам не хватает энергии для атаки " << psecond.ATTACKS[2].ATCK_NAME;


            cout << endl << "Введите \"4\" для того чтобы пропустить ход" << endl;




            input_check(attack_id);

            switch (attack_id)
            {
            case 1:
            {
                /*int attack_damage = psecond.ATTACKS.ATTACK_1.DAMAGE - pfirst.STATS.DEFENCE;
                if (attack_damage >= 0)
                    pfirst.STATS.HEALTH -= attack_damage;
                break;*/

                int attack_damage = (first_weak * psecond.ATTACKS[0].DAMAGE) - pfirst.STATS.DEFENCE;
                second_energy -= psecond.ATTACKS[0].ENERGY;
                if (attack_damage >= 0)
                    pfirst.STATS.HEALTH -= attack_damage;
                break;
            }
            case 2:
            {
                int attack_damage = (first_weak * psecond.ATTACKS[1].DAMAGE) - pfirst.STATS.DEFENCE;
                second_energy -= psecond.ATTACKS[1].ENERGY;
                if (attack_damage >= 0)
                    pfirst.STATS.HEALTH -= attack_damage;
                break;
            }
            case 3:
            {
                int attack_damage = (first_weak * psecond.ATTACKS[2].DAMAGE) - pfirst.STATS.DEFENCE;
                second_energy -= psecond.ATTACKS[2].ENERGY;
                if (attack_damage >= 0)
                    pfirst.STATS.HEALTH -= attack_damage;
                break;
            }
            default:
                break;
            }

            if (pfirst.STATS.HEALTH <= 0)
            {
                cout << psecond.NAME << " Побеждает";
                break;
            }
            else if (psecond.STATS.HEALTH <= 0)
            {
                cout << pfirst.NAME << " Побеждает";
                break;
            }

            /*if (psecond.STATS.HEALTH <= 0)
            {
                cout << psecond.NAME << " Побеждает";
                break;
            }*/

            fta++;
            second_energy += 5;
            if (second_energy > 50)
                second_energy = 50;

            cout << "Конец хода. Теперь ходит " << pfirst.NAME << endl;
        }
        round++;
    }
}

vector<string> myFunc(string myString)
{
    vector<string> traits;

    string SubString;
    for (int i = 0; i < myString.size(); i++)
    {
        char x = myString[i];
        if (x != ' ')
        {
            if ((i + 1) == myString.size())
            {
                SubString.push_back(x);
                traits.push_back(SubString);
                SubString.clear();

            }

            SubString.push_back(x);
        }
        else if(x == ' ')
        {
            traits.push_back(SubString);
            SubString.clear();
        }
    }
    return traits;
}


Pokemon* parse_pokemons()
{
    std::ifstream file;
    file.open("D:\\Mess\\source\\pokeman\\pokeman\\inn.txt");
    
    if (file.is_open())
    {
        string temp;
        int k = 0;
        for (string line; getline(file, line); )
        {
            k++;
        }
        //cout << k;
        
        file.close();

        
        file.open("D:\\Mess\\source\\pokeman\\pokeman\\inn.txt");

        if (file.is_open())
        {
            Pokemon* poke_temp = new Pokemon[k];
            for (int i = 0; i < k; i++)
            {
                //temp.clear();
                std::getline(file, temp);
                vector<string> traits = myFunc(temp);
                for (string a : traits)
                {
                    //cout << a;
                }

                poke_temp[i].ID = std::stoi(traits[0]);
                poke_temp[i].NAME = traits[1];
                poke_temp[i].TYPE = parse_string_to_pok_type(traits[2]);
                poke_temp[i].STATS.HEALTH = std::stoi(traits[3]);
                poke_temp[i].STATS.DEFENCE = std::stoi(traits[4]);
                poke_temp[i].STATS.WEAKNESS = parse_string_to_pok_type(traits[5]);
                poke_temp[i].STATS.SPEED = std::stoi(traits[6]);

                poke_temp[i].ATTACKS[0].ATCK_NAME = traits[7];
                poke_temp[i].ATTACKS[0].DAMAGE = std::stoi(traits[8]);
                poke_temp[i].ATTACKS[0].ENERGY = std::stoi(traits[9]);

                poke_temp[i].ATTACKS[1].ATCK_NAME = traits[10];
                poke_temp[i].ATTACKS[1].DAMAGE = std::stoi(traits[11]);
                poke_temp[i].ATTACKS[1].ENERGY = std::stoi(traits[12]);

                poke_temp[i].ATTACKS[2].ATCK_NAME = traits[13];
                poke_temp[i].ATTACKS[2].DAMAGE = std::stoi(traits[14]);
                poke_temp[i].ATTACKS[2].ENERGY = std::stoi(traits[15]);
            }

            return poke_temp;
        }
        else
        {
            cout << "File didnt open";
            file.close();
            return nullptr;
        }
    }
    else
    {
        cout << "File didnt open";
        file.close();
        return nullptr;
    }
}

//std::ostream& operator << (std::ostream& os, Pokemon& poke)
//{
//    return os << poke.xxxx << " " << poke.xxxx;
//}

int main()
{
    //setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Pokemon* pokemon_db = parse_pokemons();
    //cout << " " << pokemon_db[0].NAME << " " << pokemon_db[0].TYPE << " " << pokemon_db[0].STATS.WEAKNESS;
    if (pokemon_db != nullptr)
        fight(pokemon_db[0], pokemon_db[1]);
    else
        cout << "Ошибка!";

    //if (infile.is_open())
    //{
    //    Pokemon* Bulba = new Pokemon;
    //    Pokemon* Aboba = new Pokemon;
    //    int type_f, type_s, weak_f, weak_s;

    //    infile >> Bulba->ID;
    //    infile >> Bulba->NAME;
    //    infile >> type_f;
    //    Bulba->TYPE = pokemon_type(type_f);
    //    infile >> Bulba->STATS.HEALTH;
    //    infile >> Bulba->STATS.DEFENCE;
    //    infile >> weak_f;
    //    Bulba->STATS.WEAKNESS = pokemon_type(weak_f);
    //    infile >> Bulba->STATS.SPEED;
    //    for (int i = 0; i < 3; i++)
    //    {
    //        infile >> Bulba->ATTACKS[i].ATCK_NAME >> Bulba->ATTACKS[i].DAMAGE >> Bulba->ATTACKS[i].ENERGY;
    //    }
    //    

    //    infile >> Aboba->ID;
    //    infile >> Aboba->NAME;
    //    infile >> type_s;
    //    Aboba->TYPE = pokemon_type(type_s);
    //    infile >> Aboba->STATS.HEALTH;
    //    infile >> Aboba->STATS.DEFENCE;
    //    infile >> weak_s;
    //    Aboba->STATS.WEAKNESS = pokemon_type(weak_s);
    //    infile >> Aboba->STATS.SPEED;
    //    for (int i = 0; i < 3; i++)
    //    {
    //        infile >> Aboba->ATTACKS[i].ATCK_NAME >> Aboba->ATTACKS[i].DAMAGE >> Aboba->ATTACKS[i].ENERGY;
    //    }
    //    //Bulba->fight(*Bulba, *Aboba);
    //}
    //else
    //{
    //    cout << "File did not open";
    //}

    ////vector<string> test;
    //////string testt = "Aboba 123 zavr";
    ////test = myFunc("Aboba 123 zavr");
    ////for (string x : test)
    ////{
    ////    cout << x;
    ////}
    
}

