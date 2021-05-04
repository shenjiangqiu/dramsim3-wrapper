#[link(name = "dramsim3_wrapper")]
extern "C" {
    pub(super) fn get_dramsim3() -> *mut libc::c_void;
    pub(super) fn delete_dramsim3(dramsim: *mut libc::c_void);
    pub(super) fn dramsim3_send(
        dramsim: *mut libc::c_void,
        addr: u64,
        is_write: libc::boolean_t,
    ) -> libc::boolean_t;
    pub(super) fn dramsim3_get(dramsim: *mut libc::c_void) -> u64;
    pub(super) fn dramsim3_tick(dramsim: *mut libc::c_void);
    pub(super) fn dramsim3_ret_available(dramsim: *mut libc::c_void) -> libc::boolean_t;
    pub(super) fn dramsim3_available(dramsim: *mut libc::c_void, addr: u64, is_write: libc::boolean_t) -> libc::boolean_t;
    pub(super) fn dramsim3_get_channel_id(dramsim: *mut libc::c_void, addr: u64) -> libc::c_int;
}