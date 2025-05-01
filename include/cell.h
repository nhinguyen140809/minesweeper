#ifndef CELL_H
#define CELL_H

class Cell {
    private:
        bool is_mine;
        bool is_opened;
        bool is_flagged;

        int mine_count;
        int flag_count;
        int closed_count;
        unsigned char x;
        unsigned char y;
        unsigned char mouse_state;

    public:
        Cell();

        void set_mine();
        bool is_mine();

        void open();
        bool is_opened();

        void flag();
        bool is_flagged();

        void set_mine_count(int count);
        int get_mine_count();

        void set_flag_count(int count);
        int get_flag_count();

        void set_closed_count(int count);
        int get_closed_count();
};


#endif // CELL_H