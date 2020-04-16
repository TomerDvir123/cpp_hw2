#include "FamilyTree.hpp"
#include <iostream>
#include <string>


using namespace std;
using namespace family;

Tree::Tree(string name) {
    this->MyName = name;
    this->Father = NULL;
    this->Mother = NULL;
    this->depth = 0;
    this->key = 0;
    this->rel = "";
    this->found=false;
}

Tree Tree::curr(Tree *now, string name) {
    Tree temp = *now;
    if (now->MyName == name) {
        this->key = 1;
        return temp;

    }
    if (now->Mother != NULL && now->MyName != name && this->key != 1) {
        temp = curr(now->Mother, name);
    }
    if (now->Father != NULL && now->MyName != name && this->key != 1) {
        temp = curr(now->Father, name);
    }

    if (temp.MyName == name)
        return temp;

}

Tree Tree::addFather(string name, string father) {

    Tree *temp = this;
    Tree temp2 = curr(temp, name);
    this->key = 0;
    if (temp2.MyName == name) {
        if (temp2.Father == NULL) {
            temp2.Father = new Tree(father);
            temp2.Father->MyName = father;

            string temp3 = curr2(temp, name, "");
            this->key = 0;
            int i = 0;
            while (temp->MyName != name) {
                if (temp3[i] == 'f') {
                    temp = temp->Father;
                    i++;
                }
                if (temp3[i] == 'm') {
                    temp = temp->Mother;
                    i++;
                }

            }

            temp2.Father->depth = i + 1;
            int r = i + 1;


            if (r == 0) {
                cout << name + " it's me";

            } else if (r == 1) {

                temp2.Father->rel = "father";
            } else if (r == 2) {

                temp2.Father->rel = "grandfather";
            } else if (r > 2) {
                string times = "";
                int k = 2;
                while (k < r) {
                    times = times + "great-";
                    k++;
                }
                temp2.Father->rel = times + "grandfather";
            }
            temp->Father = temp2.Father;
        }
        else {
            //  cout << name + " has father\n";
            throw std::invalid_argument(name + " has a father\n");

        }
    }
    else {
        cout << name + " doesnt exist\n";
        throw std::invalid_argument(name + " doesnt exist\n");
    }

    return *this;

}

Tree Tree::addMother(string name, string mother) {
    Tree *temp = this;
    Tree temp4 = curr(temp, name);
    this->key = 0;
    if (temp4.MyName == name) {
        if (temp4.Mother == NULL) {
            temp4.Mother = new Tree(mother);
            temp4.Mother->MyName = mother;

            string temp3 = curr2(temp, name, "");
            this->key = 0;
            int i = 0;
            while (temp->MyName != name) {
                if (temp3[i] == 'f') {
                    temp = temp->Father;
                    i++;
                }
                if (temp3[i] == 'm') {
                    temp = temp->Mother;
                    i++;
                }

            }

            temp4.Mother->depth = i + 1;
            int r = i + 1;


            if (r == 0) {
                cout << name + " it's me";

            } else if (r == 1) {

                temp4.Mother->rel = "mother";
            } else if (r == 2) {

                temp4.Mother->rel = "grandmother";
            } else if (r > 2) {
                string times = "";
                int k = 2;
                while (k < r) {
                    times = times + "great-";
                    k++;
                }
                temp4.Mother->rel = times + "grandmother";
            }
            temp->Mother = temp4.Mother;
        }
        else {

            throw std::invalid_argument(name + " has a mother\n");

        }
    }
    else {
        throw std::invalid_argument(name + " doesnt exist\n");
    }

    return *this;


}

string Tree::relation(string name) {
    // this->key=0;
    // cout << name +" is ";

    Tree *temp = this;
    Tree temp2 = curr(temp, name);
    this->key = 0;
    //cout << temp2.MyName << " is: " << temp2.depth << "\n";
    string temp3 = curr2(temp, name, "");
    //cout << temp3;
    int i = 2;
    int r = 0;
    r = temp2.depth;
    if (r == 0) {
        cout << name + " it's me";
        return name;

    } else if (r == 1) {
        if (temp3[1] == 'm') {
            cout << name + " it's the mother of  " + temp->MyName;
            return "mother";

        } else {
            cout << name + " it's the father of  " + temp->MyName;
            return "father";

        }
    } else if (r == 2) {
        if (temp3[2] == 'm') {
            cout << name + " it's the grandmother of  " + temp->MyName;
            return "grandmother";
        } else {
            cout << name + " it's the grandfather of  " + temp->MyName;
            return "grandfather";

        }
    } else if (r > 2)
    {
        string times = "";
        while(i<r)
        {
            times = times + "great-";
            i++;
        }
        if (temp3[temp2.depth-1] == 'm') {
            cout << name + " it's the "+ times +"grandmother of  " + temp->MyName;
            return times + "grandmother";
        } else {
            cout << name + " it's the "+ times +"grandfather of  " + temp->MyName;
            return times + "grandfather";

        }
    }

}
////////////////
string Tree::find_helper(Tree *now, string name ) {
    Tree temp = *now;
    string n = temp.MyName;
    if (now->rel == name) {
        this->key = 1;
        this->found = true;
        return n;
    }
    if (now->Mother != NULL && now->rel != name && this->key != 1 && this->found!=true) {
        n = find_helper(now->Mother, name);
    }
    if (now->Father != NULL && now->rel != name && this->key != 1 && this->found!=true) {
        n = find_helper(now->Father, name);
    }

    if (temp.rel == name) {
        this->found = true;
        return n;
    }

    if (this->key == 1) {
        this->found = true;
        return n;
    }
    if(this->found==false )
    {
        return "";
    }
}
/////////////////

string Tree::find(string rel) {
    // string p = new string();
    string p = find_helper(this, rel);
    this->key=0;
    this->found=false;
    if(p==""){cout << "\nnot found";}
    //cout << p;
    // delete &rel;
    return p;
}

void Tree::display() {

}

void Tree::remove(string name) {

}

/**
 *     Tree temp = *now;
    if(now->MyName==name)
    {
        this->key=1;
        return temp;

    }
    if(now->Mother!=NULL && now->MyName!=name && this->key!=1)
    {
        temp = curr(now->Mother,name);
    }
    if(now->Father!=NULL && now->MyName!=name && this->key!=1 )
    {
        temp = curr(now->Father,name);
    }

    if(temp.MyName==name)
        return temp;

 * @param now
 * @param name
 * @param ans
 * @return
 */
string Tree::curr2(Tree *now, string name, string ans) {
    Tree temp = *now;
    string t = ans;
    if (now->MyName == name) {
        this->key = 1;
        return t;
    }

    if (now->Father != NULL && now->MyName != name && this->key != 1) {
        t = curr2(now->Father, name, ans + "f");
    }
    if (now->Mother != NULL && now->MyName != name && this->key != 1) {
        t = curr2(now->Mother, name, ans + "m");
    }
    if (this->key == 1) {
        return t;
    }

}
