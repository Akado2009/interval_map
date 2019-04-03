#include <map>
#include <iostream>
#include <limits>

template<typename K, typename V>
void print_map(std::map<K, V> real_map) {
    std::cout << "########################" << std::endl;
    for(const auto &[key, value]: real_map) {
        std::cout << key << ": " << value << std::endl;
    }
    std::cout << "########################" << std::endl;
}

template<typename K, typename V>
class interval_map {
	std::map<K,V> m_map;
public:
    // constructor associates whole range of K with val by inserting (K_min, val)
    // into the map
    interval_map( V const& val) {
        m_map.insert(m_map.end(),std::make_pair(std::numeric_limits<K>::lowest(),val));
    }
    

    // Assign value val to interval [keyBegin, keyEnd).
    // Overwrite previous values in this interval.
    // Conforming to the C++ Standard Library conventions, the interval
    // includes keyBegin, but excludes keyEnd.
    // If !( keyBegin < keyEnd ), this designates an empty interval,
    // and assign must do nothing.

    std::map<K, V> get_mmap(){
        return m_map;
    }
    void assign( K const& keyBegin, K const& keyEnd, V const& val ) {
// INSERT YOUR SOLUTION HERE
        typedef typename std::map<K, V>::iterator iterator;
        if (!(keyBegin < std::numeric_limits<K>::lowest())) {
            // max?
            if (keyBegin < keyEnd) {
                iterator left, right;

                left = --m_map.upper_bound(keyBegin);
                right = m_map.lower_bound(keyEnd);

                V tmp_value;
                int count = 0;
                for(auto it = left; it != right; ++it, count++) tmp_value = it->second;

                iterator true_left = left;
                iterator last = ++left;
                std::advance(last, count - 1);
                m_map.erase(left, last);

                if (true_left->second != val) m_map[keyBegin] = val;

                if (right->first == keyEnd) {
                    if (right->second == val) m_map.erase(right);
                }
                else {
                    if ((--right)->second != tmp_value) m_map[keyEnd] = tmp_value;
                }
            }
        }
    }

    // look-up of the value associated with key
    V const& operator[]( K const& key ) const {
        return ( --m_map.upper_bound(key) )->second;
    }
};

// Many solutions we receive are incorrect. Consider using a randomized test
// to discover the cases that your implementation does not handle correctly.
// We recommend to implement a test function that tests the functionality of
// the interval_map, for example using a map of unsigned int intervals to char.



int main () {
    interval_map<unsigned short, char> shit('A');
    // shit.assign(3, 5, 'B');
    // shit.assign(3, 5, 'A');
    // shit.assign(0, 10, 'B');
    shit.assign(0, std::numeric_limits<unsigned short>::max(), 'B');
    // shit.assign(4, 6, 'C');
    // shit.assign(2, 6, 'B');
    // shit.assign(7, 10, 'C');
    // shit.assign(2, 10, 'D');
    // shit.assign(4, 5, 'C');
    // shit.assign(0, 5, 'B');
    // shit.assign(2, 5, 'C');

    std::map<unsigned short, char> mm = shit.get_mmap();
    print_map(mm);
    return 0;
}