
#pragma once
#include <QAbstractTableModel>
#include <vector>
#include "Coat.h"

class WatchlistTableModel : public QAbstractTableModel {
    Q_OBJECT

private:
    std::vector<Coat> coats;
public:
    WatchlistTableModel(const std::vector<Coat>& coats, QObject* parent = nullptr)
        : QAbstractTableModel(parent), coats(coats) {

    }
    int rowCount(const QModelIndex& parent = QModelIndex()) const override {
        return static_cast<int>(coats.size());
    }
    int columnCount(const QModelIndex& parent = QModelIndex()) const override {
        return 5;
    }
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override {
        if (role == Qt::DisplayRole) {
            const Coat& m = coats[index.row()];
            switch (index.column()) {
            case 0: return QString::fromStdString(m.getSize());
            case 1: return QString::fromStdString(m.getColor());
            case 2: return m.getPrice();
            case 3: return m.getQuantity();
            case 4: return QString::fromStdString(m.getPhoto());
            }
        }
        return {};
    }
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
        if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
            switch (section) {
            case 0: return "Size";
            case 1: return "Color";
            case 2: return "Price";
            case 3: return "Quantity";
            case 4: return "Photo";
            }
        }
        return {};
    }
    void setCoats(const std::vector<Coat>& newCoats) {
        beginResetModel();
        coats = newCoats;
        endResetModel();
    }
};
