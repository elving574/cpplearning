const { Client, Collection } = require('discord.js-selfbot-v13');
const client = new Client();

let whitelisted = ["919312613786144890", "464110281623207956", "1022609307390451722"]

client.on('ready', async () => {
  console.log(`${client.user.username} is ready!`);
})

client.on("messageCreate", message => {
  if (message.content == 'ping') {
    message.reply('pong');
  }
});

client.on("messageCreate", message => {
  if (message.content == 'who do we love?') {
    message.reply('kids');
  }
});

// Create a map to store the users that are being annoyed
const annoyedUsers = new Map();

client.on('messageCreate', async message => {
  // Check if the message starts with .annoy
  if (message.content.startsWith('.annoy') && whitelisted.includes(message.author.id)) {
    // Get the user mentioned in the message
    const mentionedUser = message.mentions.users.first();

    // Check if the user exists
    if (!mentionedUser) {
      message.reply('You need to mention a user to annoy them!');
      return;
    }

    // Add the user to the map
    if (!annoyedUsers.has(mentionedUser.id)) {
      annoyedUsers.set(mentionedUser.id, message.author.id);
      message.reply(`You are now annoying ${mentionedUser.username}!`);
    } else {
      message.reply(`You are already annoying ${mentionedUser.username}!`);
    }
  }
  else if (message.content.startsWith('.stopannoy') && whitelisted.includes(message.author.id)) {
    // Check if the user is annoying someone
    if (annoyedUsers.has(message.author.id)) {
      // Get the user that is being annoyed
      const annoyedUser = client.users.cache.get(annoyedUsers.get(message.author.id));

      // Remove the user from the map
      annoyedUsers.delete(annoyedUser.id);

      // Send a message to the user
      message.reply(`You are no longer annoying ${annoyedUser.username}!`);
    } else {
      // Send a message to the user
      message.reply('You are not annoying anyone right now!');
    }
  }




  // Check if the user is being annoyed
  if (annoyedUsers.has(message.author.id)) {
    // Get the user that is annoying them
    const annoyingUser = client.users.cache.get(annoyedUsers.get(message.author.id));

    // Send the message to the annoying user in the same channel
    message.channel.send(`${message.content}`);
  }
})

client.login('NzEwMjMxMTQzMzcwNDU3MTk3.GmRwTY.dc_5knUqoXK8SkcFHwU8C8v_cJ7XudQMUilEkY');