/***************************************************************************
 *   copyright       : (C) 2003-2007 by Pascal Brachet                     *
 *   http://www.xm1math.net/texmaker/                                      *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "aboutdialog.h"
#include "utilsVersion.h"
#include "utilsSystem.h"
#include "updatechecker.h"

AboutDialog::AboutDialog(QWidget *parent)
: QDialog(parent)
{
    ui.setupUi(this);
    
    // FORZAR EL NUEVO LOGO DE IGUANA EN EL ABOUT DIALOG (75% del ancho)
    if (ui.label) {
        int targetWidth = qRound(this->width() * 0.75);
        if (targetWidth < 250) targetWidth = 350; // Mínimo razonable por si la ventana es muy pequeña
        
        // Usamos iguana.png (512x512) en lugar de logo128.png para máxima nitidez
        QPixmap highResLogo(":/images/iguana.png");
        QPixmap scaledLogo = highResLogo.scaled(targetWidth, targetWidth, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        
        ui.label->setPixmap(scaledLogo);
        ui.label->setAlignment(Qt::AlignCenter);
        
        QAction *act = new QAction("large", this);
        connect(act, SIGNAL(triggered()), SLOT(largeLogo()));
        ui.label->addAction(act);
        ui.label->setContextMenuPolicy(Qt::ActionsContextMenu);
    }
    
    setText();
    connect(UpdateChecker::instance(), SIGNAL(dataParsed(QString)), SLOT(setText(QString)));
    UpdateChecker::instance()->check(true, -2);
}

AboutDialog::~AboutDialog()
{
}

void AboutDialog::largeLogo()
{
    QDialog *dlg = new QDialog(nullptr);
    dlg->setAttribute(Qt::WA_DeleteOnClose);
    dlg->setLayout(new QHBoxLayout(dlg));
    QLabel *label = new QLabel(dlg);
    label->setPixmap(QPixmap(":/images/splash_large.png"));
    dlg->layout()->addWidget(label);
    dlg->setWindowTitle("About Iguana");
    dlg->exec();
}

void AboutDialog::setText(QString latestVersion) {
    QString changelogPath = findResourceFile("CHANGELOG.md");
    if(changelogPath.isEmpty()){
        changelogPath="https://iguana-org.github.io/CHANGELOG.html";
    }else{
        if(!changelogPath.startsWith("/")){
            changelogPath="/"+changelogPath;
        }
        changelogPath="file://"+changelogPath;
    }
    if (latestVersion=="") latestVersion = tr("couldn't retrieve data");
    
    
    ui.textBrowser->setOpenExternalLinks(true);
    ui.textBrowser->setHtml(
        QString("<h2>About Iguana</h2>"
                "<p><b>An IDE for LaTeX with AI Corpus Integration</b></p>"
                "<p>Version 1.0.0alpha0 (git %1)</p>"
                "<p>Using Qt Version %2, compiled with Qt %3 %4</p>"
                "<hr>"
                "<p><b>Iguana</b> is a fork of <b>TeXstudio</b>, which is a fork of <b>TeXmaker</b>.</p>"
                "<p>Copyright &copy; 2026 Manuel L&oacute;pez Mateos<br>"
                "Copyright &copy; 2008-2025 The TeXstudio Team<br>"
                "Copyright &copy; 2003-2007 Pascal Brachet (TeXmaker)</p>"
                "<p>This program is free software; you can redistribute it and/or modify "
                "it under the terms of the GNU General Public License as published by "
                "the Free Software Foundation; either version 2 of the License, or "
                "(at your option) any later version.</p>"
                "<hr>"
                "<p><b>Iguana adds to TeXstudio:</b></p>"
                "<ul>"
                "<li><b>Build Corpus:</b> Generate auditable Markdown corpora for AI training "
                "via the tex2waldo pipeline</li>"
                "<li><b>OpenWALDO Integration:</b> Provenance-rich academic publishing "
                "with Zenodo DOIs and CC-BY-4.0 licensing</li>"
                "</ul>"
                "<hr>"
// Busca la sección "<p><b>Documentation:</b></p>" y cámbiala por:
"<p><b>Documentation:</b></p>"
"<ul>"
"<li><a href=\"https://en.wikibooks.org/wiki/LaTeX\">LaTeX Reference</a></li>"
"<li><a href=\"https://github.com/mlmateos/iguana\">Iguana User Manual (Wiki)</a></li>"
"<li><a href=\"https://github.com/mlmateos/iguana\">Iguana Project Home</a></li>"
"<li><a href=\"https://github.com/mlmateos/tex2waldo\">tex2waldo Pipeline</a></li>"
"<li>Latest stable version: %5<br>"
"<a href=\"%6\">Changelog</a></li>"
"</ul>"
                "<hr>"
                "<p><i>Original TeXstudio credits:</i> Benito van der Zander, Jan Sundermeyer, Daniel Braun, Tim Hoffmann<br>"
                "TeXmaker: Pascal Brachet<br>"
                "QCodeEdit: Luc Bruant<br>"
                "html conversion: Joël Amblard</i><br>"
                "Iguana contains code from Hunspell (GPL), QtCreator (GPL), KILE (GPL) and SyncTeX.<br>"
                "Iguana uses the PDF viewer of TeXworks, DSingleApplication, TexTablet, QuaZip, To Title Case, flowlayout, and adwaita-qt.</p>")
        .arg(TEXSTUDIO_GIT_REVISION ? TEXSTUDIO_GIT_REVISION : "n/a")
        .arg(qVersion())
        .arg(QT_VERSION_STR)
        .arg(COMPILED_DEBUG_OR_RELEASE)
        .arg(latestVersion)
        .arg(changelogPath)
    );
}
