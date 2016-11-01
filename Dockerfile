# time docker build -t rosjoy .
FROM ubuntu:14.04
MAINTAINER Gabriel Araujo

# Intall ROS
RUN apt-get update && apt-get install -y \
    software-properties-common \
    apt-utils \
    wget \
    ca-certificates

RUN wget http://packages.ros.org/ros.key -O - | apt-key add -
RUN echo "deb http://packages.ros.org/ros/ubuntu trusty main" > /etc/apt/sources.list.d/ros-latest.list
RUN apt-get update && apt-get install -y \
    ros-indigo-desktop-full

#Add basic user
ENV USERNAME aluno
ENV PULSE_SERVER /run/pulse/native
RUN useradd -m $USERNAME && \
    echo "$USERNAME:$USERNAME" | chpasswd && \
    usermod --shell /bin/bash $USERNAME && \
    usermod -aG sudo $USERNAME && \
    echo "$USERNAME ALL=(ALL) NOPASSWD:ALL" >> /etc/sudoers.d/$USERNAME && \
    chmod 0440 /etc/sudoers.d/$USERNAME && \
    # Replace 1000 with your user/group id
    usermod  --uid 1000 $USERNAME && \
    groupmod --gid 1000 $USERNAME


RUN rosdep init
USER aluno
RUN rosdep update

USER root

# Intall some basic CLI tools
RUN apt-get install -y \
    curl \
    screen \
    byobu \
    fish \
    git \
    glances \
    iputils-ping \
    net-tools \
    sudo 

CMD ["bash"]

# Intall some basic GUI and sound libs
RUN apt-get install -y \
        xz-utils file locales dbus-x11 pulseaudio dmz-cursor-theme \
        fonts-dejavu fonts-liberation hicolor-icon-theme \
        libcanberra-gtk3-0 libcanberra-gtk-module libcanberra-gtk3-module \
        libasound2 libgtk2.0-0 libdbus-glib-1-2 libxt6 libexif12 \
        libgl1-mesa-glx libgl1-mesa-dri \
    && update-locale LANG=C.UTF-8 LC_MESSAGES=POSIX

# Intall some basic GUI tools
RUN apt-get install -y \
    terminator \
    cmake 

RUN apt-get update && apt-get install -y \
    ros-indigo-navigation 
    ros-indigo-rqt \
    ros-indigo-rqt-common-plugins


#Install firefox browser for network debuging
RUN apt-get install -y firefox 

#Install Google Chrome, run using 'google-chrome --sand-box'
# RUN wget -q -O - "https://dl-ssl.google.com/linux/linux_signing_key.pub" | sudo apt-key add - \
#  && echo "deb http://dl.google.com/linux/chrome/deb/ stable main" > /etc/apt/sources.list.d/google-chrome.list \
#  && apt-get update \
#  && apt-get install -y google-chrome-stable


#Setup .bashrc for ROS
RUN echo "source /opt/ros/indigo/setup.bash" >> /home/$USERNAME/.bashrc && \
    #Fix for qt and X server errors
    echo "export QT_X11_NO_MITSHM=1" >> /home/$USERNAME/.bashrc && \
    # cd to home on login
    echo "cd" >> /home/$USERNAME/.bashrc 

RUN apt-get update && apt-get install -y \
    ros-indigo-gmapping

# Install sublime-text
RUN mkdir -p /usr/share/icons/hicolor/16x16/apps/
RUN mkdir -p /usr/share/icons/hicolor/32x32/apps/
RUN mkdir -p /usr/share/icons/hicolor/48x48/apps/
RUN mkdir -p /usr/share/icons/hicolor/128x128/apps/
RUN mkdir -p /usr/share/icons/hicolor/256x256/apps/
RUN apt-get update && \
    apt-get install -y python-software-properties htop

RUN add-apt-repository ppa:webupd8team/sublime-text-3 && \
    apt-get update && apt-get install -y sublime-text-installer && \
    apt-get install -y libglib2.0-dev libx11-dev libgtk2.0-0
RUN rm -rf /var/lib/apt/lists/*

# Set locale to UTF8 
RUN locale-gen --no-purge en_US.UTF-8
RUN update-locale LANG=en_US.UTF-8
RUN dpkg-reconfigure locales
ENV LANGUAGE en_US.UTF-8
ENV LANG en_US.UTF-8 
ENV LC_ALL en_US.UTF-8 
RUN export uid=1000 gid=1000
#    mkdir -p /home/aluno && \
#    echo "aluno:x:${uid}:${gid}:Developer,,,:/home/aluno:/bin/bash" >> /etc/passwd && \
#    echo "aluno:x:${uid}:" >> /etc/group && \
#    echo "aluno ALL=(ALL) NOPASSWD: ALL" > /etc/sudoers.d/aluno && \
#    chmod 0440 /etc/sudoers.d/aluno && \
#    chown ${uid}:${gid} -R /home/aluno

RUN mkdir -p '/home/aluno/.config/sublime-text-3/Packages'
RUN mkdir -p '/home/aluno/.config/sublime-text-3/Installed Packages' && cd '/home/aluno/.config/sublime-text-3/Installed Packages'
RUN wget https://sublime.wbond.net/Package%20Control.sublime-package --no-check-certificate
RUN mv 'Package Control.sublime-package' '/home/aluno/.config/sublime-text-3/Installed Packages/'
#RUN chmod 777 -R /home/aluno
# share workspace directory VOLUME ["/workspace"]

RUN apt-get update && apt-get install -y \
    ros-indigo-joy \
    jstest-gtk

#Change user
USER aluno

# Setup catkin workspace
RUN bin/bash -c "echo 'source /opt/ros/indigo/setup.bash' >> ~/.bashrc && \
                 source /opt/ros/indigo/setup.bash && \
                 mkdir -p ~/catkin_ws/src && \
                 cd ~/catkin_ws/src && \
                 catkin_init_workspace && \
                 cd ~/catkin_ws/ && \
                 catkin_make && \
                 echo 'source ~/catkin_ws/devel/setup.bash' >> ~/.bashrc"
