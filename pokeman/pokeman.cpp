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
using std::ifstream;
using std::ofstream;

enum pokemon_type {
    NORMAL, FIRE, WATER, ELECTRIC, GRASS,
    ICE, FIGHTING, POISON, GROUND, FLYING,
    PSYCHIC, BUG, ROCK, GHOST, DRAGON, DARK,
    STEEL, FAIRY
};

void input_check( int&input_var )
{
    cin >> input_var;
    while (cin.fail() || (input_var != 1 && input_var != 2 && input_var != 3 && input_var != 4)) // �������� 1/2
    {
        //cout << input_var;
        cout << "������ �����" << endl;
        cin.clear();
        cin.ignore(cin.rdbuf()->in_avail());
        cin >> input_var;
    }
}

pokemon_type parse_string_to_pok_type(string temp)
{
    vector<string> mas{"NORMAL", "FIRE", "WATER", "ELECTRIC", "GRASS", "ICE", "FIGHTING", "POISON", "GROUND", "FLYING", "PSYCHIC", "BUG", "ROCK", "GHOST", "DRAGON", "DARK", "STEEL", "FAIRY"};

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
        int DEFENCE;
        pokemon_type WEAKNESS;
        int SPEED;
    }STATS;

    struct
    {
        string ATCK_NAME;
        int DAMAGE;
        int ENERGY;
    }ATTACKS[3];
};

Pokemon* parse_pokemons(int& count_pokes)
{
    ifstream file;
    file.open("Text.txt");

    if (file.is_open())
    {
        string temp;
        int k = 0, l = 0;
        vector<bool> fails;
        int for_i=0;
        for (string line; getline(file, line);++for_i)
        {
            l++;
            if (line == "" || (line[0] - '0' > 9))
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

        file.open("Text.txt");

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
    Pokemon* Parsed_pokes;


    Pokemon** Pokes_ptr;
    int pokes_size = 0;
    int real_pokes_size = 0;

    void out_pokes()
    {
        for (int i = 0; i < real_pokes_size; i++)
        {
            cout << Pokes_ptr[i]->NAME << "(" << Pokes_ptr[i]->ID << ") ";
        }
        cout << endl;

        cout << "��������� ��������� �� �����: " << count_pokes << endl;
        cout << "��������� ������ � �������� �������" << real_pokes_size << endl;
        cout << "������ ���������� ������ ��� ������" << pokes_size << endl;
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

    poke_space()
    {
        Parsed_pokes = parse_pokemons(count_pokes);

        while (pokes_size < count_pokes)
        {
            expand_pokes();
        }

        for (int i = real_pokes_size; i < count_pokes; ++i)
        {
            Pokes_ptr[i] = &Parsed_pokes[i];
            ++real_pokes_size;
        }

    }

};

//int first_to_attack()
void fight(Pokemon pfirst, Pokemon psecond)
{
    cout << "��� ������� �����: " << pfirst.NAME << " � " << psecond.NAME << endl;
    int fta;
    if (pfirst.STATS.SPEED >= psecond.STATS.SPEED)
        fta = 0;
    else
        fta = 1;

    if (fta)
        cout << "������ ������� " << psecond.NAME << endl;
    else
        cout << "������ ������� " << pfirst.NAME << endl;

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
        cout << "�����: " << round << " �������������� ���������: " <<
            pfirst.NAME << " �������� - " << pfirst.STATS.HEALTH << " ������� - " << first_energy <<
            "   " << psecond.NAME << " �������� - " << psecond.STATS.HEALTH << " ������� - " << second_energy;
        cout << "\n";
        
        if (fta % 2 == 0)
        {
            int attack_id;
            string fname = pfirst.NAME;
            string sname = psecond.NAME;

            /*cout << "�������� ����� ������ " << psecond.NAME;
            cout << endl << "������� \"1\" ��� ����� " << pfirst.ATTACKS.ATTACK_1.ATCK_NAME
                << " ��� ������� " << pfirst.ATTACKS.ATTACK_1.DAMAGE;

            cout << endl << "������� \"2\" ��� ����� " << pfirst.ATTACKS.ATTACK_2.ATCK_NAME
                << " ��� ������� " << pfirst.ATTACKS.ATTACK_2.DAMAGE;

            cout << endl << "������� \"3\" ��� ����� " << pfirst.ATTACKS.ATTACK_3.ATCK_NAME
                << " ��� ������� " << pfirst.ATTACKS.ATTACK_3.DAMAGE;
            cout << endl;*/

            cout << "�������� ����� ������ " << psecond.NAME;

            if (second_weak == 2)
                cout << "\n������� " << sname << " ���� ������ ����� " << fname;

            if (pfirst.ATTACKS[0].ENERGY - first_energy <= 0)
            {
                cout << endl << "������� \"1\" ��� ����� " << pfirst.ATTACKS[0].ATCK_NAME
                    << " ��� ������� " << (second_weak * pfirst.ATTACKS[0].DAMAGE) - psecond.STATS.DEFENCE << " � �������� " << pfirst.ATTACKS[0].ENERGY;
            }
            else
                cout << endl << "��� �� ������� ������� ��� ����� " << pfirst.ATTACKS[0].ATCK_NAME;

            if (pfirst.ATTACKS[1].ENERGY - first_energy <= 0)
            {
                cout << endl << "������� \"2\" ��� ����� " << pfirst.ATTACKS[1].ATCK_NAME
                    << " ��� ������� " << (second_weak * pfirst.ATTACKS[1].DAMAGE) - psecond.STATS.DEFENCE << " � �������� " << pfirst.ATTACKS[1].ENERGY;
            }
            else
                cout << endl << "��� �� ������� ������� ��� ����� " << pfirst.ATTACKS[1].ATCK_NAME;

            if (pfirst.ATTACKS[2].ENERGY - first_energy <= 0)
            {
                cout << endl << "������� \"3\" ��� ����� " << pfirst.ATTACKS[2].ATCK_NAME
                    << " ��� ������� " << (second_weak * pfirst.ATTACKS[2].DAMAGE) - psecond.STATS.DEFENCE << " � �������� " << pfirst.ATTACKS[2].ENERGY;
            }
            else
                cout << endl << "��� �� ������� ������� ��� ����� " << pfirst.ATTACKS[2].ATCK_NAME;


            cout << endl << "������� \"4\" ��� ���� ����� ���������� ���" << endl;

            input_check(attack_id);


            switch (attack_id)
            {
            case 1:
            {
                //cout << "�� ������� �����: " << pfirst.ATTACKS[0].ATCK_NAME;

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
                cout << psecond.NAME << " ���������";
                break;
            }
            else if (psecond.STATS.HEALTH <= 0)
            {
                cout << pfirst.NAME << " ���������";
                break;
            }



            fta++;
            first_energy += 5;
            if (first_energy > 50)
                first_energy = 50;

            cout << "����� ����. ������ ����� " << psecond.NAME << endl;
        }

        else
        {
            // �������� ��������
            int attack_id;
            string fname = pfirst.NAME;
            string sname = psecond.NAME;

            cout << "�������� ����� ������ " << pfirst.NAME;
            if (first_weak == 2)
                cout << "\n������� " << fname << " ���� ������ ����� " << sname;

            if (psecond.ATTACKS[0].ENERGY - first_energy <= 0)
            {
                cout << endl << "������� \"1\" ��� ����� " << psecond.ATTACKS[0].ATCK_NAME
                    << " ��� ������� " << (first_weak * psecond.ATTACKS[0].DAMAGE) - pfirst.STATS.DEFENCE << " � �������� " << psecond.ATTACKS[0].ENERGY;
            }
            else
                cout << endl << "��� �� ������� ������� ��� ����� " << psecond.ATTACKS[0].ATCK_NAME;

            if (psecond.ATTACKS[1].ENERGY - first_energy <= 0)
            {
                cout << endl << "������� \"2\" ��� ����� " << psecond.ATTACKS[1].ATCK_NAME
                    << " ��� ������� " << (first_weak * psecond.ATTACKS[1].DAMAGE) - pfirst.STATS.DEFENCE << " � �������� " << psecond.ATTACKS[1].ENERGY;
            }
            else
                cout << endl << "��� �� ������� ������� ��� ����� " << psecond.ATTACKS[1].ATCK_NAME;

            if (psecond.ATTACKS[2].ENERGY - first_energy <= 0)
            {
                cout << endl << "������� \"3\" ��� ����� " << psecond.ATTACKS[2].ATCK_NAME
                    << " ��� ������� " << (first_weak * psecond.ATTACKS[2].DAMAGE) - pfirst.STATS.DEFENCE << " � �������� " << psecond.ATTACKS[2].ENERGY;
            }
            else
                cout << endl << "��� �� ������� ������� ��� ����� " << psecond.ATTACKS[2].ATCK_NAME;


            cout << endl << "������� \"4\" ��� ���� ����� ���������� ���" << endl;




            input_check(attack_id);

            // ���������� �� ������
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
                cout << psecond.NAME << " ���������";
                break;
            }
            else if (psecond.STATS.HEALTH <= 0)
            {
                cout << pfirst.NAME << " ���������";
                break;
            }

            /*if (psecond.STATS.HEALTH <= 0)
            {
                cout << psecond.NAME << " ���������";
                break;
            }*/

            fta++;
            second_energy += 5;
            if (second_energy > 50)
                second_energy = 50;

            cout << "����� ����. ������ ����� " << pfirst.NAME << endl;
        }
        round++;
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


    poke_space Pokemon_db;
    Pokemon* pt = new Pokemon;
    *pt = Pokemon_db.Parsed_pokes[Pokemon_db.count_pokes - 1];

    Pokemon_db.pb(pt);
    Pokemon_db.pb_all(Pokemon_db.Parsed_pokes, 5);
    Pokemon_db.out_pokes();

    fight(*(Pokemon_db.Pokes_ptr[3]), *(Pokemon_db.Pokes_ptr[8]));

    //fight(*(Pokemon_db.Pokes_ptr[1]), *(Pokemon_db.Pokes_ptr[3]));
}

