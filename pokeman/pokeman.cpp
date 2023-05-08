#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <fstream>
#include <functional>
#include <Windows.h>


typedef unsigned int uint;

using std::cin;
using std::cout;
using std::endl;
using std::swap;
using std::vector;
using std::string;
using std::getline;
using std::ifstream;
using std::ofstream;

enum pokemon_type {
    NORMAL, FIRE, WATER, ELECTRIC, GRASS,
    ICE, FIGHTING, POISON, GROUND, FLYING,
    PSYCHIC, BUG, ROCK, GHOST, DRAGON, DARK,
    STEEL, FAIRY
};

//[min, max]
void fight_input_check( int&input_var , bool* check_mas, const int min, const int max)
{
    cin >> input_var;
    while (cin.fail() || input_var > max || input_var < min || !check_mas[input_var-1] || (input_var != 1 && input_var != 2 && input_var != 3 && input_var != 4)) // проблема 1/2
    {
        //cout << input_var;
        cout << "Ошибка ввода" << endl;
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail());
        cin >> input_var;
    }
}

//[min, max]
void fight_input_check(int& input_var, const int min, const int max)
{
    cin >> input_var;
    while (cin.fail() || input_var > max || input_var < min ) // проблема 1/2
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
    vector<string> mas{"NORMAL", "FIRE", "WATER", "ELECTRIC", "GRASS", "ICE", "FIGHTING", "POISON", "GROUND", "FLYING", "PSYCHIC", "BUG", "ROCK", "GHOST", "DRAGON", "DARK", "STEEL", "FAIRY"};
    //cout << temp;

    for (int i = 0; i < temp.length(); i++)
        temp[i] = toupper(temp[i]);

    //cout << temp;
    for (int i = 0; i < mas.size() ; ++i)
    {
        if (temp == mas[i])
            return pokemon_type(i);
    }
    return pokemon_type(0);
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
        else if (x == ' ')
        {
            traits.push_back(SubString);
            SubString.clear();
        }
    }
    return traits;
}

struct Pokemon
{
    uint ID;
    string NAME;
    pokemon_type TYPE;

    struct
    {
        int HEALTH;
        int HEALTH_COPY;
        int DEFENCE;
        pokemon_type WEAKNESS;
        int SPEED;
    }STATS;

    const static int attacks_size=3;
    struct
    {
        string ATCK_NAME;
        int DAMAGE;
        int ENERGY;
    }ATTACKS[attacks_size];

    struct
    {
        int energy = 50;
        bool weak = false;
    }for_fight;

    void out()
    {
        cout << ID << " " << NAME << " " << TYPE << " " << STATS.HEALTH << " " << STATS.DEFENCE << " " << STATS.WEAKNESS << " " << STATS.SPEED << " ";
        for (int i = 0; i < attacks_size; ++i)
        {
            cout << ATTACKS[i].ATCK_NAME << " " << ATTACKS[i].DAMAGE << " " << ATTACKS[i].ENERGY << " ";
        }
        cout << for_fight.energy << " " << for_fight.weak;
        cout << "\n";
    }
};

Pokemon* parse_pokemons(int& count_pokes, const char * Filename)
{
    ifstream file;
    file.open(Filename);

    if (file.is_open())
    {
        string temp;
        int k = 0, l = 0;
        vector<bool> fails;
        int for_i=0;
        for (string line; getline(file, line);++for_i)
        {
            l++;
            if (line[0] == '#' || line == "" || line.length() < 59 || (line[0] - '0' > 9))
            {
                //cout << "yes";
                fails.push_back(0);
                continue;
            }
            k++;
            fails.push_back(1);
        }
        count_pokes = k;
        //cout << k;

        file.close();

        if (k == 0)
            return nullptr;

        file.open(Filename);

        if (file.is_open())
        {
            Pokemon* poke_temp = new Pokemon[k];

            for (int i = 0, j = 0; i < l; ++i)
            {
                //temp.clear();
                getline(file, temp);
                vector<string> traits = myFunc(temp);
                if (fails[i] == false)
                    continue;
                //for (string a : traits)
                //{
                //    //cout << a;
                //}

                poke_temp[j].ID = std::stoi(traits[0]);
                poke_temp[j].NAME = traits[1];
                poke_temp[j].TYPE = parse_string_to_pok_type(traits[2]);
                poke_temp[j].STATS.HEALTH = std::stoi(traits[3]);
                poke_temp[j].STATS.DEFENCE = std::stoi(traits[4]);
                poke_temp[j].STATS.WEAKNESS = parse_string_to_pok_type(traits[5]);
                poke_temp[j].STATS.SPEED = std::stoi(traits[6]);

                poke_temp[j].ATTACKS[0].ATCK_NAME = traits[7];
                poke_temp[j].ATTACKS[0].DAMAGE = std::stoi(traits[8]);
                poke_temp[j].ATTACKS[0].ENERGY = std::stoi(traits[9]);

                poke_temp[j].ATTACKS[1].ATCK_NAME = traits[10];
                poke_temp[j].ATTACKS[1].DAMAGE = std::stoi(traits[11]);
                poke_temp[j].ATTACKS[1].ENERGY = std::stoi(traits[12]);

                poke_temp[j].ATTACKS[2].ATCK_NAME = traits[13];
                poke_temp[j].ATTACKS[2].DAMAGE = std::stoi(traits[14]);
                poke_temp[j].ATTACKS[2].ENERGY = std::stoi(traits[15]);

                poke_temp[j].STATS.HEALTH_COPY = poke_temp[j].STATS.HEALTH;
                j++;
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

struct poke_space
{
    int count_pokes = 0;
    Pokemon* Parsed_pokes = nullptr;

    Pokemon** Pokes_ptr = nullptr;
    int pokes_size = 0;
    int real_pokes_size = 0;

    poke_space(const char * Filename)
    {
        Parsed_pokes = parse_pokemons(count_pokes, Filename);

        while (pokes_size < count_pokes)
        {
            expand_pokes();
        }

        for (int i = real_pokes_size; i < count_pokes; ++i)
        {
            Pokes_ptr[i] = &Parsed_pokes[i];
            ++real_pokes_size;
        }

        cout << "Покемонов прочитано из файла: " << count_pokes << endl;
        cout << "Покемонов сейчас в основном массиве " << real_pokes_size << endl;
        cout << "Размер выделенной памяти под массив " << pokes_size << endl;
        cout << "\n";
    }

    ~poke_space()
    {
        if (count_pokes > 1)
            delete[] Parsed_pokes;
        
        if (count_pokes == 1)
            delete Parsed_pokes;
        
        delete Pokes_ptr;
    }

    void out_pokes()
    {
        for (int i = 0; i < real_pokes_size; i++)
        {
            cout << Pokes_ptr[i]->NAME << "(" << Pokes_ptr[i]->ID << ") ";
        }
        cout << endl;
    }

    void out_pokes_noid()
    {
        for (int i = 0; i < real_pokes_size; i++)
        {
            cout << i+1 << " " << Pokes_ptr[i]->NAME << "\n";
        }
        cout << endl;
    }

    void check_pokes()
    {
        for (int i = 0; i < real_pokes_size; ++i)
        {
            Pokes_ptr[i]->out();
        }
    }

    void expand_pokes()
    {
        if (pokes_size == 0)
        {
            Pokes_ptr = new Pokemon*;
            Pokes_ptr[0] = nullptr;
            pokes_size = 1;
        }
        else if( Pokes_ptr != nullptr)
        {
            int new_size = ++pokes_size;
            Pokemon** tmp = new Pokemon * [new_size];
            for (int i = 0; i < pokes_size ; ++i)
            {
                tmp[i] = Pokes_ptr[i];
            }
            for (int j = pokes_size; j < new_size; ++j)
            {
                tmp[j] = nullptr;
            }
            delete[] Pokes_ptr;
            Pokes_ptr = tmp;
            pokes_size = new_size;
            tmp = nullptr;
        }
    }

    void pb(Pokemon* pokemon)
    {
        expand_pokes();
        Pokes_ptr[real_pokes_size++] = pokemon;
    }

    void pb(Pokemon pokemon)
    {
        expand_pokes();
        Pokes_ptr[real_pokes_size++] = &pokemon;
    }
    
    void pb_all(Pokemon* Pokemons, const int size)
    {
        while (pokes_size - real_pokes_size < size)
        {
            expand_pokes();
        }

        for (int i = 0; i < size; ++i)
        {
            Pokes_ptr[real_pokes_size++] = &Pokemons[i];
        }

    }

    void fight()
    {
        Pokemon** pfirst = new Pokemon*;
        Pokemon** psecond = new Pokemon*;

        cout << "Выберите двух покемонов по номеру в списке: \n";
        out_pokes_noid();
        cout << "\n";
        bool* check_mas = new bool[real_pokes_size];
        for (int j = 0; j < real_pokes_size; ++j)
        {
            *(check_mas + j) = true;
        }

        int first_i = 0, second_i = 0;
        fight_input_check(first_i, check_mas, 0, real_pokes_size);
        first_i--;
        check_mas[first_i] = false;
        cout << "\nВы выбрали: " << Pokes_ptr[first_i]->NAME << "\n";
        fight_input_check(second_i, check_mas, 0, real_pokes_size);
        second_i--;
        cout << "\nВы выбрали: " << Pokes_ptr[second_i]->NAME << "\n";

        *pfirst = Pokes_ptr[first_i];
        *psecond = Pokes_ptr[second_i];

        delete[] check_mas;
        
        
        cout << "Бой начался между: " << (*pfirst)->NAME << " и " << (*psecond)->NAME << endl;

        int fta = 0;

        if ((*pfirst)->STATS.SPEED > (*psecond)->STATS.SPEED)
            fta = 0;
        else if ((*pfirst)->STATS.SPEED == (*psecond)->STATS.SPEED)
            fta = rand() % 2;
        else
            fta = 1;

        //cout << "\n" << fta << "\n";

        if (fta)
            cout << "Первым атакует " << (*psecond)->NAME << endl;
        else
            cout << "Первым атакует " << (*pfirst)->NAME << endl;

        int round = 1;

        if ((*pfirst)->STATS.WEAKNESS == (*psecond)->TYPE)
        {
            (*pfirst)->for_fight.weak = true;
        }
        else
            (*pfirst)->for_fight.weak = false;

        if ((*pfirst)->TYPE == (*psecond)->STATS.WEAKNESS)
        {
            (*psecond)->for_fight.weak = true;
        }
        else
            (*psecond)->for_fight.weak = false;

        if (fta)
            swap(pfirst, psecond);

        while (true)
        {
            cout << "Раунд: " << round << " Характеристики покемонов: " <<
                (*pfirst)->NAME << " здоровье - " << (*pfirst)->STATS.HEALTH << " Энергия - " << (*pfirst)->for_fight.energy <<
                "   " << (*psecond)->NAME << " здоровье - " << (*psecond)->STATS.HEALTH << " Энергия - " << (*psecond)->for_fight.energy;
            cout << "\n";

            string fname, sname;

            int attack_id;

            fname = (*pfirst)->NAME;
            sname = (*psecond)->NAME;


            cout << "Выберите атаку против " << (*psecond)->NAME;

            if ((*psecond)->for_fight.weak)
                cout << "\nПокемон " << sname << " слаб против аттак " << fname;


            /*auto list_attacks = [](Pokemon** pfirst, Pokemon** psecond, int i) {

                if ((*pfirst)->ATTACKS[i].ENERGY - (*pfirst)->for_fight.energy <= 0)
                {
                    cout << endl << "Введите \" << i <<\" для атаки " << (*pfirst)->ATTACKS[i].ATCK_NAME
                        << " она нанесет " << (((*pfirst)->for_fight.weak + 1) * (*pfirst)->ATTACKS[i].DAMAGE) - (*psecond)->STATS.DEFENCE << " и затратит " << (*pfirst)->ATTACKS[i].ENERGY;
                }
                else
                    cout << endl << "Вам не хватает энергии для атаки " << (*pfirst)->ATTACKS[i].ATCK_NAME;

                return 0;
            };

            for (int i = 0; i < (*pfirst)->attacks_size; i++)
            {
                list_attacks(pfirst, psecond, i);
            }*/

            bool attacks_energy_check[(*pfirst)->attacks_size];
            for (int m = 0; m < (*pfirst)->attacks_size; m++)
            {
                attacks_energy_check[m] = true;
            }

            for (int i = 0; i <= (*pfirst)->attacks_size; ++i)
            {
                if ((*pfirst)->attacks_size == i)
                {
                    cout << endl << "Введите \"" << i + 1 << "\" для того чтобы пропустить ход" << endl;
                    break;
                }

                if ((*pfirst)->ATTACKS[i].ENERGY - (*pfirst)->for_fight.energy <= 0)
                {
                    cout << endl << "Введите \"" << i + 1 << "\" для атаки " << (*pfirst)->ATTACKS[i].ATCK_NAME
                        << " она нанесет " << (((*pfirst)->for_fight.weak + 1) * (*pfirst)->ATTACKS[i].DAMAGE) - (*psecond)->STATS.DEFENCE << " и затратит " << (*pfirst)->ATTACKS[i].ENERGY;
                    attacks_energy_check[i] = true;
                }
                else
                {
                    cout << endl << "Вам не хватает энергии для атаки " << (*pfirst)->ATTACKS[i].ATCK_NAME;
                    attacks_energy_check[i] = false;
                }
            }



            fight_input_check(attack_id, attacks_energy_check, 1, (*pfirst)->attacks_size + 1);

            int second_weak = ((*psecond)->for_fight.weak + 1);

            for (int i = 0; i < (*pfirst)->attacks_size; ++i)
            {
                if ((attack_id - 1) == (*pfirst)->attacks_size)
                {
                    (*pfirst)->for_fight.energy += 5;
                    if ((*pfirst)->for_fight.energy > 50)
                        (*pfirst)->for_fight.energy = 50;
                    break;
                }

                if (i == (attack_id - 1))
                {
                    int attack_damage = (second_weak * (*pfirst)->ATTACKS[i].DAMAGE) - (*psecond)->STATS.DEFENCE;
                    (*pfirst)->for_fight.energy -= (*pfirst)->ATTACKS[i].ENERGY;
                    if (attack_damage >= 0)
                        (*psecond)->STATS.HEALTH -= attack_damage;

                    break;
                }
            }

            (*psecond)->for_fight.energy += 5;
            if ((*psecond)->for_fight.energy > 50)
                (*psecond)->for_fight.energy = 50;

            if ((*pfirst)->STATS.HEALTH <= 0)
            {
                cout << (*psecond)->NAME << " Побеждает";
                break;
            }
            else if ((*psecond)->STATS.HEALTH <= 0)
            {
                cout << (*pfirst)->NAME << " Побеждает";
                break;
            }



            cout << "Конец хода. Теперь ходит " << (*psecond)->NAME << endl;

            swap(pfirst, psecond);
            round++;
        }

        (*pfirst)->STATS.HEALTH = (*pfirst)->STATS.HEALTH_COPY;
        (*psecond)->STATS.HEALTH = (*psecond)->STATS.HEALTH_COPY;

        (*pfirst)->for_fight.energy = 50;
        (*psecond)->for_fight.energy = 50;

        (*pfirst)->for_fight.weak = false;
        (*psecond)->for_fight.weak = false;

    }

    Pokemon* fight(Pokemon* pfirstt, Pokemon* psecondd)
    {
        Pokemon** pfirst = new Pokemon*;
        Pokemon** psecond = new Pokemon*;

        *pfirst = pfirstt;
        *psecond = psecondd;
        
        cout << "Бой начался между: " << (*pfirst)->NAME << " и " << (*psecond)->NAME << endl;

        int fta = 0;

        if ((*pfirst)->STATS.SPEED > (*psecond)->STATS.SPEED)
            fta = 0;
        else if ((*pfirst)->STATS.SPEED == (*psecond)->STATS.SPEED)
            fta = rand() % 2;
        else
            fta = 1;

        //cout << "\n" << fta << "\n";

        if (fta)
            cout << "Первым атакует " << (*psecond)->NAME << endl;
        else
            cout << "Первым атакует " << (*pfirst)->NAME << endl;

        int round = 1;

        if ((*pfirst)->STATS.WEAKNESS == (*psecond)->TYPE)
        {
            (*pfirst)->for_fight.weak = true;
        }
        else
            (*pfirst)->for_fight.weak = false;

        if ((*pfirst)->TYPE == (*psecond)->STATS.WEAKNESS)
        {
            (*psecond)->for_fight.weak = true;
        }
        else
            (*psecond)->for_fight.weak = false;

        if (fta)
            swap(pfirst, psecond);

        while (true)
        {
            cout << "Раунд: " << round << " Характеристики покемонов: " <<
                (*pfirst)->NAME << " здоровье - " << (*pfirst)->STATS.HEALTH << " Энергия - " << (*pfirst)->for_fight.energy <<
                "   " << (*psecond)->NAME << " здоровье - " << (*psecond)->STATS.HEALTH << " Энергия - " << (*psecond)->for_fight.energy;
            cout << "\n";

            string fname, sname;

            int attack_id;

            fname = (*pfirst)->NAME;
            sname = (*psecond)->NAME;


            cout << "Выберите атаку против " << (*psecond)->NAME;

            if ((*psecond)->for_fight.weak)
                cout << "\nПокемон " << sname << " слаб против аттак " << fname;


            /*auto list_attacks = [](Pokemon** pfirst, Pokemon** psecond, int i) {

                if ((*pfirst)->ATTACKS[i].ENERGY - (*pfirst)->for_fight.energy <= 0)
                {
                    cout << endl << "Введите \" << i <<\" для атаки " << (*pfirst)->ATTACKS[i].ATCK_NAME
                        << " она нанесет " << (((*pfirst)->for_fight.weak + 1) * (*pfirst)->ATTACKS[i].DAMAGE) - (*psecond)->STATS.DEFENCE << " и затратит " << (*pfirst)->ATTACKS[i].ENERGY;
                }
                else
                    cout << endl << "Вам не хватает энергии для атаки " << (*pfirst)->ATTACKS[i].ATCK_NAME;

                return 0;
            };

            for (int i = 0; i < (*pfirst)->attacks_size; i++)
            {
                list_attacks(pfirst, psecond, i);
            }*/

            bool attacks_energy_check[(*pfirst)->attacks_size];
            for (int m = 0; m < (*pfirst)->attacks_size; m++)
            {
                attacks_energy_check[m] = true;
            }

            for (int i = 0; i <= (*pfirst)->attacks_size; ++i)
            {
                if ((*pfirst)->attacks_size == i)
                {
                    cout << endl << "Введите \"" << i + 1 << "\" для того чтобы пропустить ход" << endl;
                    break;
                }

                if ((*pfirst)->ATTACKS[i].ENERGY - (*pfirst)->for_fight.energy <= 0)
                {
                    cout << endl << "Введите \"" << i + 1 << "\" для атаки " << (*pfirst)->ATTACKS[i].ATCK_NAME
                        << " она нанесет " << (((*pfirst)->for_fight.weak + 1) * (*pfirst)->ATTACKS[i].DAMAGE) - (*psecond)->STATS.DEFENCE << " и затратит " << (*pfirst)->ATTACKS[i].ENERGY;
                    attacks_energy_check[i] = true;
                }
                else
                {
                    cout << endl << "Вам не хватает энергии для атаки " << (*pfirst)->ATTACKS[i].ATCK_NAME;
                    attacks_energy_check[i] = false;
                }
            }



            fight_input_check(attack_id, attacks_energy_check, 1, (*pfirst)->attacks_size + 1);

            int second_weak = ((*psecond)->for_fight.weak + 1);

            for (int i = 0; i < (*pfirst)->attacks_size; ++i)
            {
                if ((attack_id - 1) == (*pfirst)->attacks_size)
                {
                    (*pfirst)->for_fight.energy += 5;
                    if ((*pfirst)->for_fight.energy > 50)
                        (*pfirst)->for_fight.energy = 50;
                    break;
                }

                if (i == (attack_id - 1))
                {
                    int attack_damage = (second_weak * (*pfirst)->ATTACKS[i].DAMAGE) - (*psecond)->STATS.DEFENCE;
                    (*pfirst)->for_fight.energy -= (*pfirst)->ATTACKS[i].ENERGY;
                    if (attack_damage >= 0)
                        (*psecond)->STATS.HEALTH -= attack_damage;

                    break;
                }
            }

            (*psecond)->for_fight.energy += 5;
            if ((*psecond)->for_fight.energy > 50)
                (*psecond)->for_fight.energy = 50;

            if ((*pfirst)->STATS.HEALTH <= 0)
            {
                cout << (*psecond)->NAME << " Побеждает";
                return (*psecond);
                
            }
            else if ((*psecond)->STATS.HEALTH <= 0)
            {
                cout << (*pfirst)->NAME << " Побеждает";
                return (*pfirst);
            }



            cout << "Конец хода. Теперь ходит " << (*psecond)->NAME << endl;

            swap(pfirst, psecond);
            round++;
        }

        (*pfirst)->STATS.HEALTH = (*pfirst)->STATS.HEALTH_COPY;
        (*psecond)->STATS.HEALTH = (*psecond)->STATS.HEALTH_COPY;

        (*pfirst)->for_fight.energy = 50;
        (*psecond)->for_fight.energy = 50;

        (*pfirst)->for_fight.weak = false;
        (*psecond)->for_fight.weak = false;

    }

    Pokemon* fight_fast(Pokemon* pfirstt, Pokemon* psecondd)
    {
        Pokemon** pfirst = new Pokemon*;
        Pokemon** psecond = new Pokemon*;

        *pfirst = pfirstt;
        *psecond = psecondd;

        int fta = 0;

        if ((*pfirst)->STATS.SPEED > (*psecond)->STATS.SPEED)
            fta = 0;
        else if ((*pfirst)->STATS.SPEED == (*psecond)->STATS.SPEED)
            fta = rand() % 2;
        else
            fta = 1;

        int round = 1;

        if ((*pfirst)->STATS.WEAKNESS == (*psecond)->TYPE)
        {
            (*pfirst)->for_fight.weak = true;
        }
        else
            (*pfirst)->for_fight.weak = false;

        if ((*pfirst)->TYPE == (*psecond)->STATS.WEAKNESS)
        {
            (*psecond)->for_fight.weak = true;
        }
        else
            (*psecond)->for_fight.weak = false;

        if (fta)
            swap(pfirst, psecond);

        while (true)
        {
            bool attacks_energy_check[(*pfirst)->attacks_size];
            for (int m = 0; m < (*pfirst)->attacks_size; m++)
            {
                attacks_energy_check[m] = true;
            }

            for (int i = 0; i <= (*pfirst)->attacks_size; ++i)
            {
                if ((*pfirst)->attacks_size == i)
                {
                    break;
                }

                if ((*pfirst)->ATTACKS[i].ENERGY - (*pfirst)->for_fight.energy <= 0)
                {
                    attacks_energy_check[i] = true;
                }
                else
                {
                    attacks_energy_check[i] = false;
                }
            }

            int attack_id = rand() % 4 + 1;
            while( !attacks_energy_check[attack_id-1] )
                attack_id = rand() % 4 + 1;

            int second_weak = ((*psecond)->for_fight.weak + 1); // чзх?

            for (int i = 0; i < (*pfirst)->attacks_size; ++i)
            {
                if ((attack_id - 1) == (*pfirst)->attacks_size)
                {
                    (*pfirst)->for_fight.energy += 5;
                    if ((*pfirst)->for_fight.energy > 50)
                        (*pfirst)->for_fight.energy = 50;
                    break;
                }

                if (i == (attack_id - 1))
                {
                    int attack_damage = (second_weak * (*pfirst)->ATTACKS[i].DAMAGE) - (*psecond)->STATS.DEFENCE;
                    (*pfirst)->for_fight.energy -= (*pfirst)->ATTACKS[i].ENERGY;
                    if (attack_damage >= 0)
                        (*psecond)->STATS.HEALTH -= attack_damage;

                    break;
                }
            }

            (*psecond)->for_fight.energy += 5;
            if ((*psecond)->for_fight.energy > 50)
                (*psecond)->for_fight.energy = 50;

            if ((*pfirst)->STATS.HEALTH <= 0)
            {
                (*pfirst)->STATS.HEALTH = (*pfirst)->STATS.HEALTH_COPY;
                (*psecond)->STATS.HEALTH = (*psecond)->STATS.HEALTH_COPY;

                (*pfirst)->for_fight.energy = 50;
                (*psecond)->for_fight.energy = 50;

                (*pfirst)->for_fight.weak = false;
                (*psecond)->for_fight.weak = false;


                return (*psecond);
            }
            else if ((*psecond)->STATS.HEALTH <= 0)
            {
                (*pfirst)->STATS.HEALTH = (*pfirst)->STATS.HEALTH_COPY;
                (*psecond)->STATS.HEALTH = (*psecond)->STATS.HEALTH_COPY;

                (*pfirst)->for_fight.energy = 50;
                (*psecond)->for_fight.energy = 50;

                (*pfirst)->for_fight.weak = false;
                (*psecond)->for_fight.weak = false;
                

                return (*pfirst);
            }

            swap(pfirst, psecond);
            round++;
        }

        

    }


    Pokemon* tournament()
    {
        if (real_pokes_size < 2)
        {
            cout << "No pokemons to fight";
            return nullptr;
        }

        ofstream outfile("tournament.txt");
		
        if (outfile.is_open())
        {
            //Pokemon** Tournament_db = new Pokemon * [real_pokes_size];
			
            //for (int i = 0; i < real_pokes_size; i++)
            //{
            //    *Tournament_db = Pokes_ptr[i];
            //}

            if (real_pokes_size == 2)
            {
				//Pokemon * winner = fight_fast(Tournament_db[0], Tournament_db[1]);

				Pokemon * winner = fight_fast(Pokes_ptr[0], Pokes_ptr[1]);
				outfile << "Победитель - " << winner->NAME << endl;
                return winner;
            }
            
            Pokemon** mas = new Pokemon * [2];
            for (int i = 0, j = 0; i < real_pokes_size; i += 2, ++j)
            {

            }
			

            if (real_pokes_size % 2 != 0)
            {

            }

            outfile.close();
            //delete[] Tournament_db;
            //return nullptr;
        }
        else
        {
			cout << "File was not created";
            outfile.close();
            return nullptr;
        }
        
        
    }
};

//std::ostream& operator << (std::ostream& os, Pokemon& poke)
//{
//    return os << poke.xxxx << " " << poke.xxxx;
//}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    /*int** ptr2 = new int*;
    int* ptr = new int;
    *ptr = 2;
    *ptr2 = ptr;*/
    //cout << *ptr << "  " << ptr << "  " << &ptr << "\n\n\n";

    poke_space Pokemon_db{ "Text.txt" };

    //test
    /*Pokemon* pt = new Pokemon;
    *pt = Pokemon_db.Parsed_pokes[Pokemon_db.count_pokes - 1];

    Pokemon_db.pb(pt);
    Pokemon_db.pb_all(Pokemon_db.Parsed_pokes, Pokemon_db.count_pokes);*/

    Pokemon_db.out_pokes();
    Pokemon_db.check_pokes();

    Pokemon_db.tournament();


  


    /*cout << "Хотите ли вы начать сражение? 0/1 :\n";
    int choice = 0;
    fight_input_check(choice, 0, 1);
    
    switch (choice)
    {
    case 1:
        Pokemon_db.fight();
        break;
    default:
        break;
    }*/

    
    cout << "\n\n";
    Pokemon_db.check_pokes();
    system("pause");
}

