/**
 ******************************************************************************
 *
 * @file       tlendtpage.h
 * @author     Tau Labs, http://taulabs.org, Copyright (C) 2014
 * @see        The GNU Public License (GPL) Version 3
 *
 * @addtogroup GCSPlugins GCS Plugins
 * @{
 * @addtogroup RfmBindWizard Setup Wizard
 * @{
 *****************************************************************************/
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, see <http://www.gnu.org/licenses/>
 */

#ifndef TLENDPAGE_H
#define TLENDPAGE_H

#include "abstractwizardpage.h"

namespace Ui {
class EndPage;
}

class TLEndPage : public AbstractWizardPage
{
    Q_OBJECT

public:
    explicit TLEndPage(RfmBindWizard *wizard, QWidget *parent = 0);
    ~TLEndPage();

private:
    Ui::EndPage *ui;
};

#endif // TLENDPAGE_H
