#include <Chiptune.hpp>
#ifdef USE_SIDPLAY
	#include <SIDPlay.hpp>
#endif
#ifdef USE_GME
	#include <GME.hpp>
#endif

Chiptune::Chiptune() :
	Module( "Chiptune" )
{
	moduleImg = QImage( ":/Chip" );

#ifdef USE_GME
	init( "GME", true );
#endif
#ifdef USE_SIDPLAY
	init( "SIDPlay", true );
#endif
}

QList< Chiptune::Info > Chiptune::getModulesInfo( const bool showDisabled ) const
{
	QList< Info > modulesInfo;
#ifdef USE_GME
	if ( showDisabled || getBool( "GME" ) )
		modulesInfo += Info( GMEName, DEMUXER, QStringList() << "ay" << "gbs" << "gym" << "hes" << "kss" << "nsf" << "nsfe" << "sap" << "spc" << "vgm" << "vgz" );
#endif
#ifdef USE_SIDPLAY
	if ( showDisabled || getBool( "SIDPlay" ) )
		modulesInfo += Info( SIDPlayName, DEMUXER, QStringList() << "sid" << ".c64" << ".prg" );
#endif
	return modulesInfo;
}
void *Chiptune::createInstance( const QString &name )
{
#ifdef USE_GME
	if ( name == GMEName )
		return new GME( *this );
#endif
#ifdef USE_SIDPLAY
	if ( name == SIDPlayName )
		return new SIDPlay( *this );
#endif
	return NULL;
}

Chiptune::SettingsWidget *Chiptune::getSettingsWidget()
{
	return new ModuleSettingsWidget( *this );
}

QMPLAY2_EXPORT_PLUGIN( Chiptune )

/**/

#include <QGridLayout>
#include <QCheckBox>

ModuleSettingsWidget::ModuleSettingsWidget( Module &module ) :
	Module::SettingsWidget( module )
{
	gmeB = new QCheckBox( "Game-Music-Emu " + tr( "włączony" ) );
	gmeB->setChecked( sets().getBool( "GME" ) );

	sidB = new QCheckBox( "SID " + tr( "włączony" ) );
	sidB->setChecked( sets().getBool( "SIDPlay" ) );

	QGridLayout *layout = new QGridLayout( this );
	layout->addWidget( gmeB );
	layout->addWidget( sidB );
}

void ModuleSettingsWidget::saveSettings()
{
	sets().set( "GME", gmeB->isChecked() );
	sets().set( "SIDPlay", sidB->isChecked() );
}