//-*- Mode: C++; indent-tabs-mode: nil; tab-width: 2 -*-
/* * Copyright (C) 2013 Brandon Schaefer
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License version 3 as
* published by the Free Software Foundation.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
* Authored by: Brandon Schaefer <brandontschaefer@gmail.com>
*/

#ifndef CELLITEM
#define CELLITEM

#include <memory>

#include <QGraphicsItem>
#include <QPainter>

#include <Cell.h>

namespace ui
{

class CellItem : public QGraphicsItem
{
public:
  typedef std::shared_ptr<CellItem> Ptr;

  CellItem(int size);
  ~CellItem();

  QRectF boundingRect() const;
  void paint(QPainter* painter, QStyleOptionGraphicsItem const* item, QWidget* parent);

  void SetStart();
  void SetFinish();

  void SetColor(QColor const& color);

  void Mark();
  void UnMark();
  bool Marked() const;

  void SetCell(Cell& cell);
  Cell const& GetCell() const;

private:
  QColor color_;
  Cell cell_;

  int size_;
  bool start_;
  bool finish_;
  bool marked_;
  bool was_marked_;
};

} // namespace ui

#endif // CELLITEM
