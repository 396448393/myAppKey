<template>
  <div ref="box">
    <el-container>
      <el-header>
        <el-menu :default-active="activeIndex" class="el-menu-demo" mode="horizontal" @select="handleSelect"
                 background-color="#545c64" text-color="#fff" active-text-color="#ffd04b">
          <el-menu-item index="1">我的家</el-menu-item>
          <el-menu-item index="2" v-if="homeForm.connectionStatus">管理员页面</el-menu-item>
        </el-menu>
      </el-header>
      <el-main>
        <home v-if="activeIndex === '1'" :homeForm="homeForm"  @changeSwitch="onChangeSwitch" @testButton="testConnection"></home>
        <manager v-if="activeIndex === '2'" :tableData="tableData"></manager>
      </el-main>
    </el-container>
  </div>
</template>

<script>
import axios from 'axios'
import Home from "/src/components/feature/Home.vue";
import Manager from "/src/components/feature/Manager.vue";

export default {
  name: "AppIndex",
  components: {Home, Manager},
  data() {
    return {
      homeForm: {
        connectionStatus: false,
        lockState: false,
      },
      activeIndex: '1',
      tableData: [{
      user: '王小虎',
    }, {
      user: '王小虎',
    }],
      hostAddress: '',
      keyId: '123123',
    }
  },
  mounted() {
    this.$refs.box.addEventListener('deviceready',()=>{
      this.onDeviceReady();
    });
    this.getConnectionStatus();
  },
  created() {

  },
  methods: {
    testConnection() {
      this.getConnectionStatus();
    },
    onDeviceReady() {
      this.$refs.box.addEventListener('online',()=>{
        this.getConnectionStatus();
      });
    },
    //页签选择
    handleSelect(key, keyPath) {
      this.activeIndex = key;
    },
    //通信测试
    connectionTest() {
      axios.get("http://"+this.hostAddress+"/inline").then(response => {
        if(response && response.data === 'works') {
          this.homeForm.connectionStatus = true;
          this.getLockState()
        }else{
          this.homeForm.connectionStatus = false;
        }
      },response=>{
        this.homeForm.connectionStatus = false;
      })
    },
    //获取用户列表
    getUserList() {
      let param = {
        "key": this.keyId
      };
      axios.post("http://"+this.hostAddress+"/getAiImage",param).then(response => {
        console.log(response);
      })
    },
    //获取锁状态
    getLockState() {
      let param = {
        "key": this.keyId
      };
      axios.post("http://"+this.hostAddress+"/getAiImage",param).then(response => {
        console.log(response);
        alert('获取锁状态'+JSON.stringify(response))
        if(response && response.data) {
          this.homeForm.lockState = true;
        }else {
          this.homeForm.lockState = false;
        }

      })
    },
    //获取连接状态
    getConnectionStatus() {
      this.isConnectWifi();
    },
    //是否连接wifi
    isConnectWifi() {
      const type = navigator.connection.type;
      if (type === Connection.WIFI) {
        networkinterface.getWiFiIPAddress((info) => {
          this.hostAddress = this.getNetAddress(info.ip,info.subnet);
          this.connectionTest();
        })
      }else {
        alert("请连接WIFI")
      }
    },
    //获取网络地址
    getNetAddress(ip, subnetMask) {
      let ip_str = '';
      let ip_arr = ip.split(".");
      let mask_arr = subnetMask.split(".");

      let ip2 = Number(ip_arr[2]);
      let ip3 = Number(ip_arr[3]);
      let mask2 = Number(mask_arr[2]);
      let mask3 = Number(mask_arr[3]);

      ip_str=(ip2&mask2)+"."+((ip3&mask3)+1);
      ip_str = ip_arr[0]+"."+ip_arr[1]+"."+ip_str;
      return ip_str;
    },
    //开
    doOpen() {
      let param = {
        "key": this.keyId
      };
      axios.post("http://"+this.hostAddress+"/open",param).then(response => {
        if(response && response.data === 'open') {
          this.homeForm.lockState = true;
        }
      })
    },
    //关
    doClose() {
      let param = {
        "key": this.keyId
      };
      axios.post("http://"+this.hostAddress+"/close",param).then(response => {
        if(response && response.data === 'close') {
          this.homeForm.lockState = false;
        }
      })
    },
    onChangeSwitch(val) {
      if(val) {
        this.doOpen();
      }else {
        this.doClose();
      }
    }
  },
  watch: {
    activeIndex(newActive,oldActive) {

    }
  }
}
</script>

<style>
.index_back {
}
</style>
