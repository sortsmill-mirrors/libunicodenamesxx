Name:		libunicodenamesxx
Version:	1.1.0
Release:	1%{?dist}.beta1
Summary:	C++ library for retrieving Unicode annotation data
#Group:		
License:	GPLv3+
URL:		http://sortsmill.bitbucket.org
Source0:	https://bitbucket.org/sortsmill/%{name}/downloads/%{name}-%{version}_beta1.tar.xz
BuildRoot:	%{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)

BuildRequires:	coreutils
BuildRequires:	pkgconfig
BuildRequires:	libunicodenames-devel >= 1.1.0-1.beta1
Requires:	libunicodenames >= 1.1.0-1.beta1

%description
LibUnicodeNames++ makes it easy for your program to retrieve the
information contained in the "NamesList" file that is published by the
Unicode Consortium.

%package devel
Summary:	C++ library for retrieving Unicode annotation data (development files)
Requires:	libunicodenamesxx = %{version}-%{release}
Requires:	pkgconfig
%description devel
LibUnicodeNames++ makes it easy for your program to retrieve the
information contained in the "NamesList" file that is published by the
Unicode Consortium.

%prep
%setup -q -n %{name}-%{version}_beta1

%build
%configure
make %{?_smp_mflags}

%check
make %{?_smp_mflags} check

%install
rm -rf %{buildroot}
make %{?_smp_mflags} install DESTDIR=%{buildroot}
rm -f %{buildroot}%{_libdir}/*.la

%clean
rm -rf %{buildroot}

%files
%defattr(-,root,root,-)
%{_libdir}/*.so.*
%lang(fr) %{_datadir}/locale/fr/LC_MESSAGES/%{name}.*

%files devel
%defattr(-,root,root,-)
%{_includedir}/*
%{_libdir}/*.so
%{_libdir}/*.a
%{_libdir}/pkgconfig/*

%doc AUTHORS README COPYING COPYING.LIB ChangeLog

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%changelog
* Tue Jul 23 2013 Barry Schwartz <sortsmill@crudfactory.com> 1.1.0-1.beta1
- upstream release 1.1.0_beta1
