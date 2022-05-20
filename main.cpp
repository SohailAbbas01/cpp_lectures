#include<iostream>
#include<string>
#include<vector>
#include <algorithm>

using namespace std;

enum ProductType {
    VEGETABLE,
    FRUITS,
    MILK,
    EGG,
    OIL,
    NUTS
};

static ProductType convertStringToEnum(string type) throw() {
    if (type == "VEGETABLE") return VEGETABLE;
    if (type == "FRUITS") return FRUITS;
    if (type == "MILK") return MILK;
    if (type == "EGG") return EGG;
    if (type == "OIL") return OIL;
    if (type == "NUTS") return NUTS;
    throw std::invalid_argument("Unimplemented item");
} 

static constexpr const char* ProductTypeToString(ProductType e) throw()
{
    switch (e)
    {
    case ProductType::VEGETABLE: return "VEGETABLE"; break;
    case ProductType::FRUITS: return "FRUITS"; break;
    case ProductType::MILK: return "MILK"; break;
    case ProductType::EGG: return "EGG"; break;
    case ProductType::OIL: return "OIL"; break;
    case ProductType::NUTS: return "NUTS";break;
    default: throw std::invalid_argument("Unimplemented item");
    }
}
struct Item {
    string Name;
    string bestBefore;
    double price;
    ProductType type;
    Item() {}
    Item(string name, string bestBefore, double price, ProductType type) {
        this->Name = name;
        this->bestBefore = bestBefore;
        this->price = price;
        this->type = type;
    }
    bool operator==(const Item& rhs) const {
        if (Name == rhs.Name && bestBefore == rhs.bestBefore && price == rhs.price && type == rhs.type) return true;
        return false;
    }
};

class Inventory {
private:
    vector<Item> items;
public:
    Inventory() {};
    void AddItem();
    void RemoveItem(string name);
    void EditItem(string name);
    Item SearchByName(string name);
    vector<Item> SearchByType(ProductType type);
};
void Inventory::AddItem() {
    string itemName, bestBefore;
    double price;
    string type;
    cout << "Enter Item Name :";
    getline(cin, itemName);
    cout << "Enter Bestbefore : ";
    getline(cin, bestBefore);
    cout << "Enter Type: ";
    getline(cin, type);
    cout << "Enter price :";
    cin >> price;
    Item item = Item( itemName, bestBefore, price, convertStringToEnum(type.c_str()) );
    items.push_back(item);
}
void Inventory::RemoveItem(string name) {
    std::vector<Item>:: iterator temp;
    Item item = SearchByName(name);
    for (auto it = items.begin(); it != items.end(); it++) {
        if (*it == item) {
            temp = it;
            break;
        }
    }
    items.erase(temp);
}
void Inventory::EditItem(string name) {
    auto it = std::find_if(items.begin(), items.end(),
        [name](const Item& x) { return x.Name == name; });
    cout << "Enter item name : ";
    getline(cin, it->Name);
    cout << "Enter best before :";
    getline(cin, it->bestBefore);
    cout << "Enter type : ";
    string type;
    getline(cin, type);
    cout << "Enter price :";
    cin >> it->price;
    cin.ignore();
    it->type = convertStringToEnum(type);
}

Item Inventory::SearchByName(string name) {
    auto it = std::find_if(items.begin(), items.end(),
        [name](const Item& x) { return x.Name == name; });
    if (it == items.end()) return Item();
    return *it;
}

vector<Item> Inventory::SearchByType(ProductType type) {
    vector <Item> result;
    for (auto it = items.begin(); it != items.end(); it++) {
        if (it->type == type) {
            result.push_back(*it);
        }
    }
    return result;
}
int main() {
	Inventory inventory = Inventory();
	bool cont = true;
	while (cont) {
		cout << "Menu Items : " << endl;
		cout << "1. Add Item" << endl;
		cout << "2. Remove Item" << endl;
		cout << "3.Edit Item" << endl;
		cout << "4.Search Item by name" << endl;
		cout << "5. Search Item by Type" << endl;
		cout << "6. Quit" << endl;
		int choice;
		cin >> choice;
		cin.ignore();
		switch (choice)
		{
		case 1: inventory.AddItem(); break;
		case 2: {
			cout << "Enter the product name: " << endl;
			string name;
			getline(cin, name);
			inventory.RemoveItem(name); break; 
		}
		case 3: {
			cout << "Enter the product name: " << endl;
			string name;
			getline(cin, name);
			inventory.EditItem(name); break;
		}
		case 4: {
			cout << "Enter the product name: " << endl;
			string name;
			getline(cin, name);

			Item item = inventory.SearchByName(name); 
			if (item.Name == "") cout << "No item Found" << endl;
			else {
				cout << "Name : " << item.Name << endl;;
				cout << "Price : " << item.price << endl;
				cout << "Best before : " << item.bestBefore << endl;
				cout << "Type : " << ProductTypeToString(item.type) << endl;
			}

			break;
		}
		case 5: {
			cout << "Enter the product type: " << endl;
			string type;
			getline(cin, type);
			vector<Item> items = inventory.SearchByType(convertStringToEnum(type));
			for (int i = 0; i < items.size(); i++) {
				Item item = items[i];
				cout << "---------------------------" << endl;
				cout << "Name : " << item.Name << endl;;
				cout << "Price : " << item.price << endl;
				cout << "Best before : " << item.bestBefore << endl;
				cout << "Type : " << ProductTypeToString(item.type) << endl;
			}
			break;
		}
		case 6: cont = false; break;
		default:
			cout << "Enter correct number" << endl;
			break;
		}
	}
};