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

#include <QStyleOptionGraphicsItem>

#include "CellItem.h"

namespace ui
{

CellItem::CellItem(int size)
 : color_(Qt::green)
 , cell_(Cell())
 , size_(size)
 , start_(false)
 , finish_(false)
 , marked_(false)
{}

QRectF CellItem::boundingRect() const
{
  return QRectF(0, 0, size_, size_);
}

void CellItem::paint(QPainter* painter, QStyleOptionGraphicsItem const* item, QWidget* widget)
{
  Q_UNUSED(widget);

  painter->setPen(QPen("#000000"));

  if (cell_.Empty())
  {
    painter->fillRect(QRectF(0, 0, size_, size_), "#000000");
  }
  else
  {
    // DOWN
    if (!cell_.DownOpen())
      painter->drawLine(0, size_, size_, size_);

    // RIGHT
    if (!cell_.RightOpen())
      painter->drawLine(size_, size_, size_, 0);
  }

  if (start_)
  {
    painter->setBrush(Qt::red);
    painter->drawEllipse(QRectF(0, 0, size_-1, size_-1));
  }
  else if (finish_)
  {
    painter->setBrush(Qt::blue);
    painter->drawEllipse(QRectF(0, 0, size_-1, size_-1));
  }

  if (marked_)
  {
    painter->setBrush(color_);
    painter->drawEllipse(QRectF(size_/4, size_/4, size_/2, size_/2));
  }
}

Cell const& CellItem::GetCell() const
{
  return cell_;
}

void CellItem::SetCell(Cell& cell)
{
  cell_ = cell;
}

void CellItem::SetColor(QColor const& color)
{
  color_ = color;
  update();
}

bool CellItem::Marked() const
{
  return marked_;
}

void CellItem::Mark()
{
  marked_ = true;
  update();
}

void CellItem::UnMark()
{
  marked_ = false;
  update();
}

void CellItem::SetStart()
{
  start_ = true;
}

void CellItem::SetFinish()
{
  finish_ = true;
}

} // namespace ui
