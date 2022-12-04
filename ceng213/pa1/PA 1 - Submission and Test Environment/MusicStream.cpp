#include "MusicStream.h"

#include <iostream>

Node<Profile> *MusicStream::getProfile(const std::string &email)
{
    Node<Profile> *curr = profiles.getFirstNode();
    for (int i = 0; i < profiles.getSize(); i++)
    {
        if (curr->data.getEmail() == email)
        {
            break;
        }
        curr = curr->next;
    }
    return curr;
}

Node<Song> *MusicStream::getSong(int songId)
{
    Node<Song> *curr = songs.getFirstNode();
    for (int i = 0; i < songs.getSize(); i++)
    {
        if (curr->data.getSongId() == songId)
        {
            break;
        }
        curr = curr->next;
    }
    return curr;
}

Node<Album> *MusicStream::getAlbum(int albumId)
{
    Node<Album> *curr = albums.getFirstNode();
    for (int i = 0; i < albums.getSize(); i++)
    {
        if (curr->data.getAlbumId() == albumId)
        {
            break;
        }
        curr = curr->next;
    }
    return curr;
}

Node<Artist> *MusicStream::getArtist(int artistId)
{
    Node<Artist> *curr = artists.getFirstNode();
    for (int i = 0; i < artists.getSize(); i++)
    {
        if (curr->data.getArtistId() == artistId)
        {
            break;
        }
        curr = curr->next;
    }
    return curr;
}

void MusicStream::addProfile(const std::string &email, const std::string &username, SubscriptionPlan plan)
{
    profiles.insertAtTheEnd(Profile(email, username, plan));
}

void MusicStream::deleteProfile(const std::string &email)
{
    Node<Profile> *profile = getProfile(email);
    Node<Profile *> *curr = profile->data.getFollowers().getFirstNode();
    for (int i = 0; i < profile->data.getFollowers().getSize(); i++)
    {
        Node<Profile *> *following = curr->data->getFollowings().getFirstNode();
        for (int i = 0; i < curr->data->getFollowings().getSize(); i++)
        {
            if (following->data->getEmail() == email)
            {
                break;
            }
            following = following->next;
        }
        curr->data->getFollowings().removeNode(following);
        curr = curr->next;
    }
    curr = profile->data.getFollowings().getFirstNode();
    for (int i = 0; i < profile->data.getFollowings().getSize(); i++)
    {
        Node<Profile *> *follower = curr->data->getFollowers().getFirstNode();
        for (int i = 0; i < curr->data->getFollowers().getSize(); i++)
        {
            if (follower->data->getEmail() == email)
            {
                break;
            }
            follower = follower->next;
        }
        curr->data->getFollowings().removeNode(follower);
        curr = curr->next;
    }
    profile->data.getFollowings().~LinkedList();
    profile->data.getFollowers().~LinkedList();
    profile->data.getPlaylists().~LinkedList();
    profiles.removeNode(profile);
}

void MusicStream::addArtist(const std::string &artistName)
{
    artists.insertAtTheEnd(Artist(artistName));
}

void MusicStream::addAlbum(const std::string &albumName, int artistId)
{
    albums.insertAtTheEnd(Album(albumName));
    getArtist(artistId)->data.addAlbum(&albums.getLastNode()->data);
}

void MusicStream::addSong(const std::string &songName, int songDuration, int albumId)
{
    songs.insertAtTheEnd(Song(songName, songDuration));
    getAlbum(albumId)->data.addSong(&songs.getLastNode()->data);
}

void MusicStream::followProfile(const std::string &email1, const std::string &email2)
{
    getProfile(email1)->data.followProfile(&getProfile(email2)->data);
}

void MusicStream::unfollowProfile(const std::string &email1, const std::string &email2)
{
    getProfile(email1)->data.unfollowProfile(&getProfile(email2)->data);
}

void MusicStream::createPlaylist(const std::string &email, const std::string &playlistName)
{
    getProfile(email)->data.createPlaylist(playlistName);
}

void MusicStream::deletePlaylist(const std::string &email, int playlistId)
{
    getProfile(email)->data.deletePlaylist(playlistId);
}

void MusicStream::addSongToPlaylist(const std::string &email, int songId, int playlistId)
{
    getPlaylist(email, playlistId)->addSong(&getSong(songId)->data);
}

void MusicStream::deleteSongFromPlaylist(const std::string &email, int songId, int playlistId)
{
    getPlaylist(email, playlistId)->dropSong(&getSong(songId)->data);
}

LinkedList<Song *> MusicStream::playPlaylist(const std::string &email, Playlist *playlist)
{
    if (getProfile(email)->data.getPlan() == premium)
    {
        return playlist->getSongs();
    }
    else
    {
        LinkedList<Song *> songs(playlist->getSongs());
        songs.insertAsEveryKthNode(&Song::ADVERTISEMENT_SONG, 2);
        return songs;
    }
}

Playlist *MusicStream::getPlaylist(const std::string &email, int playlistId)
{
    return getProfile(email)->data.getPlaylist(playlistId);
}

LinkedList<Playlist *> MusicStream::getSharedPlaylists(const std::string &email)
{
    LinkedList<Playlist *> shared_playlists;
    Node<Profile *> *following = (getProfile(email)->data.getFollowings()).getFirstNode();
    for (int i = 0; i < getProfile(email)->data.getFollowings().getSize(); i++)
    {
        Node<Playlist> *playlist = following->data->getPlaylists().getFirstNode();
        for (int j = 0; j < following->data->getPlaylists().getSize(); j++)
        {
            if (playlist->data.isShared())
            {
                shared_playlists.insertAtTheEnd(&playlist->data);
            }
            playlist = playlist->next;
        }
        following = following->next;
    }
    return shared_playlists;
}

void MusicStream::shufflePlaylist(const std::string &email, int playlistId, int seed)
{
    getPlaylist(email, playlistId)->getSongs().shuffle(seed);
}

void MusicStream::sharePlaylist(const std::string &email, int playlistId)
{
    getPlaylist(email, playlistId)->setShared(true);
}

void MusicStream::unsharePlaylist(const std::string &email, int playlistId)
{
    getPlaylist(email, playlistId)->setShared(false);
}

void MusicStream::subscribePremium(const std::string &email)
{
    getProfile(email)->data.setPlan(premium);
}

void MusicStream::unsubscribePremium(const std::string &email)
{
    getProfile(email)->data.setPlan(free_of_charge);
}

void MusicStream::print() const
{
    std::cout << "# Printing the music stream ..." << std::endl;

    std::cout << "# Number of profiles is " << this->profiles.getSize() << ":" << std::endl;
    this->profiles.print();

    std::cout << "# Number of artists is " << this->artists.getSize() << ":" << std::endl;
    this->artists.print();

    std::cout << "# Number of albums is " << this->albums.getSize() << ":" << std::endl;
    this->albums.print();

    std::cout << "# Number of songs is " << this->songs.getSize() << ":" << std::endl;
    this->songs.print();

    std::cout << "# Printing is done." << std::endl;
}